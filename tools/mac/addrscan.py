#!/usr/bin/env python3
"""Shared source scanning for the macOS port tools (gen-trap-table.py, gen-not-yet.py).

Everything here reads plain text. It finds, for every address hash:
  * its name and value (Codeware src/Red/Addresses/Library.hpp, RED4ext SDK AddressHashes.hpp),
  * whether the Mac build maps it (resolver rows, SDK rows, SDK special cases),
  * how the sources use it (RawFunc / RawPtr / UniversalRelocFunc ...), with the declared return type,
  * which source files reach the Raw symbol that wraps it.
"""
import os
import re

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
DEFAULT_SDK = os.path.abspath(os.path.join(ROOT, '..', 'RED4ext.SDK-macos', 'include'))


def read(path):
    with open(path, errors='replace') as f:
        return f.read()


def walk_sources(root, exts=('.hpp', '.cpp', '.h', '.inc')):
    for dp, dn, fn in os.walk(root):
        if '/macos/build' in dp or '/.git' in dp or '/build' in dp.split(os.sep)[-1:]:
            continue
        for f in sorted(fn):
            if f.endswith(exts):
                yield os.path.join(dp, f)


def parse_cw(path):
    return {n: int(v) for n, v in re.findall(r'constexpr\s+uint32_t\s+(\w+)\s*=\s*(\d+)\s*;', read(path))}


def parse_sdk(path):
    out = {}
    for n, v in re.findall(r'constexpr\s+std::uint32_t\s+(\w+)\s*=\s*(0x[0-9A-Fa-f]+|\d+)U?L?L?\s*;', read(path)):
        out[n] = int(v, 16) if v.lower().startswith('0x') else int(v)
    return out


def mapped_hashes(root=ROOT, sdk=DEFAULT_SDK):
    """Hashes that resolve to a Mac address without the trap table: Codeware resolver rows, the SDK row injection file,
    the SDK table rows and its special cases (stand-ins, CClass vslots, vault)."""
    out = {}
    res = read(os.path.join(root, 'macos', 'MacAddressResolver.cpp'))
    rows = read(os.path.join(root, 'macos', 'MacSdkRows.inc'))
    for src, text in (('codeware-resolver', res), ('sdk-rows-inc', rows)):
        for m in re.finditer(r'\{\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+)\s*\}', text):
            h = int(m.group(1), 0)
            out.setdefault(h, (src, int(m.group(2), 16)))
    standins = os.path.join(root, 'macos', 'MacStandIns.inc')
    if os.path.exists(standins):
        for m in re.finditer(r'STANDIN\(\s*(\d+)u?\s*,', read(standins)):
            out.setdefault(int(m.group(1)), ('stand-in', 0))
    reloc = read(os.path.join(sdk, 'RED4ext', 'Relocation-inl.hpp'))
    for m in re.finditer(r'\{\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+)\s*\}', reloc):
        out.setdefault(int(m.group(1), 0), ('sdk-table', int(m.group(2), 16)))
    for m in re.finditer(r'aHash\s*==\s*(0x[0-9A-Fa-f]+|\d+)', reloc):
        out.setdefault(int(m.group(1), 0), ('sdk-special', 0))
    return out


def balanced(text, start, open_ch='<', close_ch='>'):
    """text[start] is open_ch. Returns the index of the matching close_ch (ignoring '->' and '>>' operator noise)."""
    depth = 0
    i = start
    n = len(text)
    while i < n:
        c = text[i]
        if c == open_ch:
            depth += 1
        elif c == close_ch:
            if open_ch == '<' and i > 0 and text[i - 1] == '-':
                pass
            else:
                depth -= 1
                if depth == 0:
                    return i
        i += 1
    return -1


def split_top(text, sep=','):
    parts, depth, cur = [], 0, ''
    for i, c in enumerate(text):
        if c in '<([{':
            depth += 1
        elif c in '>)]}' and not (c == '>' and i > 0 and text[i - 1] == '-'):
            depth -= 1
        if c == sep and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += c
    parts.append(cur)
    return parts


def mask_comments(text):
    """Blank out // and /* */ comments (keeps newlines so line numbers stay correct). String literals are respected."""
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            out.append(text[i:j + 1])
            i = j + 1
        elif text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            out.append(' ' * (j - i))
            i = j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r'[^\n]', ' ', text[i:j]))
            i = j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


def strip_comments(s):
    s = re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)
    s = re.sub(r'//[^\n]*', ' ', s)
    return re.sub(r'\s+', ' ', s).strip()


def return_type_of(sig):
    """'void (*)(A, B)' or 'Handle<X> (*)(...)' -> return type text; None when sig is not a function pointer type."""
    sig = strip_comments(sig)
    m = re.search(r'\(\s*\*\s*\)\s*\(', sig)
    if not m:
        return None
    return sig[:m.start()].strip()


KINDS = ('RawFunc', 'RawPtr', 'RawOffset', 'RawVFunc', 'UniversalRelocFunc', 'UniversalRelocPtr', 'UniversalRelocVtbl')


def scan_codeware(src_dir):
    """Returns {name: [use]} for the Codeware address library. use = dict(kind, file, line, symbol, ret, sig)."""
    uses = {}
    for path in walk_sources(src_dir):
        if path.endswith('Addresses/Library.hpp'):
            continue
        text = mask_comments(read(path))
        rel = os.path.relpath(path, ROOT)
        for m in re.finditer(r'AddressLib::(\w+)', text):
            name = m.group(1)
            line = text.count('\n', 0, m.start()) + 1
            # Find the enclosing 'RawX<' opener before this match.
            head = text[:m.start()]
            k = max((head.rfind(kind + '<') for kind in KINDS))
            kind = None
            sig = ''
            if k >= 0 and m.start() - k < 400:
                kind = re.match(r'\w+', text[k:]).group(0)
                lt = k + len(kind)
                gt = balanced(text, lt)
                if gt > 0:
                    args = split_top(text[lt + 1:gt])
                    if len(args) >= 2:
                        sig = strip_comments(args[1]).strip()
            # The symbol this use defines: "constexpr auto X = " / "using X =" before the opener.
            sym = None
            if kind:
                pre = text[max(0, k - 160):k]
                mm = list(re.finditer(r'(?:constexpr\s+auto|using)\s+(\w+)\s*=', pre))
                if mm:
                    sym = mm[-1].group(1)
                    ns = list(re.finditer(r'namespace\s+(Raw(?:::\w+)*)', head))
                    if ns:
                        sym = ns[-1].group(1) + '::' + sym
            uses.setdefault(name, []).append(dict(kind=kind or 'other', file=rel, line=line, symbol=sym, sig=sig,
                                                  ret=return_type_of(sig) if sig else None))
    return uses


def scan_sdk(sdk_dir):
    uses = {}
    for path in walk_sources(sdk_dir):
        if path.endswith('Detail/AddressHashes.hpp'):
            continue
        text = mask_comments(read(path))
        rel = os.path.relpath(path, sdk_dir)
        for m in re.finditer(r'AddressHashes::(\w+)', text):
            name = m.group(1)
            line = text.count('\n', 0, m.start()) + 1
            head = text[:m.start()]
            k = max((head.rfind(kind + '<') for kind in KINDS))
            kind = None
            sig = ''
            if k >= 0 and m.start() - k < 400:
                kind = re.match(r'\w+', text[k:]).group(0)
                lt = k + len(kind)
                gt = balanced(text, lt)
                if gt > 0:
                    sig = strip_comments(text[lt + 1:gt])
                    if re.fullmatch(r'\w+', sig):
                        # UniversalRelocFunc<func_t>: find 'using func_t = ...;' closest before.
                        mm = list(re.finditer(r'using\s+' + re.escape(sig) + r'\s*=\s*([^;]+);', head[:k]))
                        if mm:
                            sig = strip_comments(mm[-1].group(1))
            # Enclosing function name, best effort: last "Class::Method(" or "Name(" definition line before.
            fn = None
            mm = list(re.finditer(r'^[A-Za-z_][^\n;{}]*?\b([A-Za-z_]\w*(?:::\w+)*)\s*\([^;{}]*\)\s*(?:const)?\s*(?:noexcept)?\s*\n?\{', head, re.M))
            if mm:
                fn = mm[-1].group(1)
            uses.setdefault(name, []).append(dict(kind=kind or 'other', file=rel, line=line, symbol=fn, sig=sig,
                                                  ret=return_type_of(sig) if sig else None))
    return uses


def scan_codeware_sdk_names(src_dir):
    """Uses of RED4ext::Detail::AddressHashes::<Name> inside Codeware's own sources (same shape as scan_sdk)."""
    uses = {}
    for path in walk_sources(src_dir):
        text = mask_comments(read(path))
        rel = os.path.relpath(path, ROOT)
        for m in re.finditer(r'AddressHashes::(\w+)', text):
            name = m.group(1)
            line = text.count('\n', 0, m.start()) + 1
            head = text[:m.start()]
            k = max((head.rfind(kind + '<') for kind in KINDS))
            kind, sig, sym = None, '', None
            if k >= 0 and m.start() - k < 400:
                kind = re.match(r'\w+', text[k:]).group(0)
                lt = k + len(kind)
                gt = balanced(text, lt)
                if gt > 0:
                    args = split_top(text[lt + 1:gt])
                    if len(args) >= 2:
                        sig = strip_comments(args[1])
                pre = text[max(0, k - 160):k]
                mm = list(re.finditer(r'(?:constexpr\s+auto|using)\s+(\w+)\s*=', pre))
                if mm:
                    sym = mm[-1].group(1)
                    ns = list(re.finditer(r'namespace\s+(Raw(?:::\w+)*)', head))
                    if ns:
                        sym = ns[-1].group(1) + '::' + sym
            uses.setdefault(name, []).append(dict(kind=kind or 'other', file=rel, line=line, symbol=sym, sig=sig,
                                                  ret=return_type_of(sig) if sig else None))
    return uses
