#!/usr/bin/env python3
"""Generate macos/NOT_YET.md: every address hash that has no Mac address yet, what uses it, and what happens on Mac.

Reads plain text only (same inputs as gen-trap-table.py, plus the Mac resolver rows). Deterministic: running it twice on
the same tree gives the same file.

Usage: gen-not-yet.py [--sdk <RED4ext.SDK include dir>] [--out macos/NOT_YET.md]
"""
import argparse
import collections
import os
import re

import addrscan as A

DATA_KINDS = ('RawPtr', 'RawOffset', 'UniversalRelocPtr', 'UniversalRelocVtbl')
FLOAT_TYPES = ('float', 'double')
SCALARS = {'void', 'bool', 'int', 'unsigned', 'char', 'short', 'long', 'float', 'double', 'size_t', 'HRESULT',
           'int8_t', 'int16_t', 'int32_t', 'int64_t', 'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t', 'uintptr_t',
           'intptr_t', 'std::size_t'}
# Small trivially copyable structs that the AArch64 ABI returns in x0/x1 (16 bytes or less, no destructor).
SMALL_PODS = {'AllocationResult': '16 bytes (void* + size_t), returned in x0/x1'}


def area_of(rel):
    parts = rel.split(os.sep)
    if len(parts) >= 3 and parts[0] == 'src' and parts[1] == 'App':
        return parts[2]
    if len(parts) >= 2 and parts[0] == 'src' and parts[1] == 'Red':
        return 'Red (shared headers)'
    if parts[0] == 'src':
        return 'plugin core'
    return 'SDK'


def classes_of(path):
    """Script-visible RTTI classes a source file defines or expands."""
    try:
        text = A.mask_comments(A.read(path))
    except OSError:
        return []
    out = []
    for m in re.finditer(r'RTTI_(?:DEFINE|EXPAND)_CLASS\(\s*([\w:]+)(?:\s*,\s*([\w:]+))?', text):
        name = m.group(1)
        out.append(name.split('::')[-1])
    return out


def classify_return(ret, kind):
    """(class, note). class: data, void, scalar, pointer, float, pod16, struct-x8, unknown."""
    if kind in DATA_KINDS:
        return 'data', 'read through a zeroed buffer'
    if ret is None:
        return 'none', 'no live use found in the sources'
    r = ret.replace('const ', '').replace('::', '::').strip()
    if r.endswith('*') or r.endswith('&'):
        return 'pointer', 'pointer or reference, trap returns null'
    base = r.split('::')[-1] if r.startswith(('std::',)) is False else r
    if r in SCALARS or base in SCALARS:
        if r in FLOAT_TYPES:
            return 'float', 'trap zeroes v0 as well'
        if r == 'void':
            return 'void', ''
        return 'scalar', 'trap returns 0'
    if r in SMALL_PODS:
        return 'pod16', SMALL_PODS[r]
    return 'struct-x8', 'returned by value: needs a per-function x8 handler or a mapping before it is called'


# Unmapped hashes that are proven not applicable on Mac (name -> reason). Everything else that is unmapped and not reached by Codeware
# on Mac is "unreached".
NOT_APPLICABLE = {
    'QuestsSystem_CreateContext': 'clang inlined the wrapper into its 18 callers; Raw::QuestsSystem::CreateContext calls the QuestContext constructor row (Mac-only id 0xC0DE0011)',
    'CNamePool_AddCString': 'the Windows table address is an unrelated vtable slot and the function is inlined; the const char* overload (CNamePool_AddCstr) is mapped and used',
    'ScriptValidator_CompareTypeName': 'the game inlines the comparison into ScriptValidator::Validate; there is no function to map or hook',
    'ResourceSerializer_ScheduleFinalizeJobs': 'Windows load path; the Mac hooks use the two load job bodies (Mac-only ids 0xC0DE0001 and 0xC0DE0002)',
    'ResourceSerializer_OnResourceReady': 'Windows load path; the Mac hooks use the two load job bodies (Mac-only ids 0xC0DE0001 and 0xC0DE0002)',
    'ResourceSerializer_OnDependenciesReady': 'Windows load path; the Mac hooks use the two load job bodies (Mac-only ids 0xC0DE0001 and 0xC0DE0002)',
    'ResourceSerializer_ExecutePostLoad': 'Windows load path; the Mac hooks use the two load job bodies (Mac-only ids 0xC0DE0001 and 0xC0DE0002)',
    'ResourceSerializer_SchedulePostLoadJobs': 'Windows load path; the Mac hooks use the two load job bodies (Mac-only ids 0xC0DE0001 and 0xC0DE0002)',
    'ResourceToken_DestructUnk38': 'inlined into ~ResourceToken on Mac (0x21C4A54 to 0x21C4ACC); the SDK destructor skips it on Apple',
    'QuestLoader_PhasePreloadCheck': 'its only user (QuestPhaseRegistry hooks) is disabled upstream and the function is inlined on Mac',
}


def apple_view(text):
    """The text as the compiler sees it on macOS: keeps the Apple side of `#if defined(__APPLE__)` / `#if !defined(__APPLE__)` blocks."""
    out = []
    stack = []
    for line in text.split('\n'):
        t = line.strip()
        m = re.match(r'#\s*if\s+(!?)\s*defined\s*\(\s*__APPLE__\s*\)\s*$', t)
        if m:
            stack.append(['apple', not m.group(1)])
            continue
        if re.match(r'#\s*if', t):
            stack.append(['other', True])
            continue
        if re.match(r'#\s*else', t):
            if stack and stack[-1][0] == 'apple':
                stack[-1][1] = not stack[-1][1]
            continue
        if re.match(r'#\s*endif', t):
            if stack:
                stack.pop()
            continue
        if all(f[1] for f in stack):
            out.append(line)
    return '\n'.join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--sdk', default=A.DEFAULT_SDK)
    ap.add_argument('--out', default=os.path.join(A.ROOT, 'macos', 'NOT_YET.md'))
    a = ap.parse_args()

    src_dir = os.path.join(A.ROOT, 'src')
    cw = A.parse_cw(os.path.join(src_dir, 'Red', 'Addresses', 'Library.hpp'))
    sdk = A.parse_sdk(os.path.join(a.sdk, 'RED4ext', 'Detail', 'AddressHashes.hpp'))
    mapped = A.mapped_hashes(A.ROOT, a.sdk)
    ucw = A.scan_codeware(src_dir)
    usdk = A.scan_sdk(a.sdk)
    usdk_cw = A.scan_codeware_sdk_names(src_dir)

    # All Codeware source text, once, for symbol reach. Seen as the Mac compiler sees it: the Windows side of an
    # `#if defined(__APPLE__)` / `#else` block does not count as a use on Mac.
    src_texts = {}
    for p in A.walk_sources(src_dir):
        src_texts[os.path.relpath(p, A.ROOT)] = A.mask_comments(apple_view(A.read(p)))
    class_cache = {}

    def file_classes(rel):
        if rel not in class_cache:
            class_cache[rel] = classes_of(os.path.join(A.ROOT, rel))
        return class_cache[rel]

    # hash -> record
    recs = {}
    for n, h in cw.items():
        r = recs.setdefault(h, dict(names=[], origin=set(), uses=[]))
        r['names'].append(n)
        r['origin'].add('Codeware')
        r['uses'] += [dict(u, via='Codeware') for u in ucw.get(n, [])]
    for n, h in sdk.items():
        r = recs.setdefault(h, dict(names=[], origin=set(), uses=[]))
        r['names'].append(n)
        r['origin'].add('SDK')
        r['uses'] += [dict(u, via='SDK') for u in usdk.get(n, [])]
        r['uses'] += [dict(u, via='Codeware') for u in usdk_cw.get(n, [])]

    by_origin = collections.Counter()
    for h in recs:
        if h in mapped:
            by_origin[mapped[h][0]] += 1

    rows = []
    for h in sorted(recs):
        if h in mapped:
            continue
        r = recs[h]
        uses = r['uses']
        kinds = [u['kind'] for u in uses if u['kind'] != 'other']
        kind = 'unused'
        if any(k in DATA_KINDS for k in kinds):
            kind = 'data'
        elif kinds:
            kind = 'func'
        # The declared return type: the first use that has one.
        ret = next((u['ret'] for u in uses if u['ret']), None)
        cls, note = classify_return(ret, 'RawPtr' if kind == 'data' else kind)
        if kind == 'func' and ret is None:
            cls, note = 'unknown', 'signature not parsed'
        symbols = sorted({u['symbol'] for u in uses if u['symbol']})
        # Reach: source files that mention a Raw symbol of this hash outside the file that declares it.
        reach = set()
        decl_files = {u['file'] for u in uses}
        for u in uses:
            sym = u['symbol']
            if not sym:
                continue
            if sym.startswith('Raw::'):
                # A use inside the declaring file itself (for example a destructor that calls the wrapper).
                short = sym.split('::')[-1]
                dtext = src_texts.get(u['file'], '')
                if len(re.findall(r'\b' + re.escape(short) + r'\b', dtext)) > 1:
                    reach.add(u['file'])
                pat = re.compile(r'\b' + re.escape(sym) + r'\b')
                for rel, text in src_texts.items():
                    if rel.endswith('Addresses/Library.hpp'):
                        continue
                    if pat.search(text):
                        reach.add(rel)
            else:
                # SDK symbol such as RED4ext::JobQueue::DispatchJob: reached through the SDK. Look for the class name
                # and the method name together in Codeware's sources.
                parts = sym.split('::')
                if len(parts) >= 2:
                    cpat = re.compile(r'\b' + re.escape(parts[-2]) + r'\b')
                    mpat = re.compile(r'\b' + re.escape(parts[-1]) + r'\b')
                    for rel, text in src_texts.items():
                        if cpat.search(text) and mpat.search(text):
                            reach.add(rel)
        reach = sorted(reach)
        areas = sorted({area_of(f) for f in reach if not f.startswith('src/Red/')}) or sorted({area_of(f) for f in reach})
        classes = sorted({c for f in reach for c in file_classes(f)})
        rows.append(dict(hash=h, names=sorted(r['names']), origin='+'.join(sorted(r['origin'])), kind=kind,
                         ret=ret, cls=cls, note=note, symbols=symbols, reach=reach, areas=areas, classes=classes,
                         decl=sorted(decl_files)))

    total = len(recs)
    unmapped = len(rows)
    cls_count = collections.Counter(r['cls'] for r in rows)
    kind_count = collections.Counter(r['kind'] for r in rows)
    area_map = collections.defaultdict(list)
    for r in rows:
        nomatch = 'Declared in Codeware, no live caller' if 'Codeware' in r['origin'] else 'RED4ext SDK internals, not called directly by Codeware'
        for ar in (r['areas'] or [nomatch]):
            area_map[ar].append(r)

    L = []
    w = L.append
    w('# Not on Mac yet')
    w('')
    w('Generated by `tools/mac/gen-not-yet.py` from the sources. Do not edit by hand; run the script again.')
    w('')
    w('Every address hash that Codeware or the RED4ext SDK asks for and that has no macOS address yet. On macOS each of')
    w('these resolves to a compile-time trap stub (`macos/MacTrap.cpp`, table `macos/MacTrapTable.inc`). The first call')
    w('logs `[cw] not on Mac yet: <name> (hash <n>) called from <image>+0x<offset>` and returns zero; a data hash reads')
    w('as zeros. The hooking driver refuses to hook a trap, so a feature whose hook target is missing is skipped with a')
    w('log line instead of patching a stub.')
    w('')
    w('## Counts')
    w('')
    w('| | hashes |')
    w('|---|---|')
    w('| Known to the sources (Codeware %d, SDK %d, shared %d) | %d |' % (
        len(cw), len(sdk), len(cw) + len(sdk) - total, total))
    mapped_here = sum(1 for h in recs if h in mapped)
    w('| Mapped to a Mac address | %d |' % mapped_here)
    for src, label in (('codeware-resolver', 'Codeware resolver rows'), ('sdk-rows-inc', 'SDK overlay rows (MacSdkRows.inc)'),
                       ('sdk-table', 'SDK table rows'), ('sdk-special', 'SDK stand-ins and CClass slots'), ('stand-in', 'plugin stand-ins (MacStandIns.inc)')):
        if by_origin.get(src):
            w('| &nbsp;&nbsp;of which %s | %d |' % (label, by_origin[src]))
    w('| **Not on Mac yet (trap stub)** | **%d** |' % unmapped)
    w('| &nbsp;&nbsp;functions with a declared wrapper (not all reached on Mac, see the status below) | %d |' % kind_count['func'])
    w('| &nbsp;&nbsp;data (pointers, tables, offsets) | %d |' % kind_count['data'])
    w('| &nbsp;&nbsp;declared but not used by any live code (commented out or dead) | %d |' % kind_count['unused'])
    w('')
    w('## What a trap does to the return value')
    w('')
    w('| class | functions | trap behaviour |')
    w('|---|---|---|')
    desc = collections.OrderedDict([
        ('void', 'nothing to return'),
        ('scalar', 'x0 = 0'),
        ('pointer', 'x0 = null'),
        ('float', 'v0 = 0.0 and x0 = x1 = 0 (`TRAP_FLT` stub)'),
        ('pod16', 'x0 = x1 = 0 (a 16 byte plain struct comes back in x0/x1)'),
        ('struct-x8', 'NOT SAFE. A struct returned through x8 (CString, Handle, DynArray, anything with a destructor or over 16 bytes) is not filled in; the caller reads uninitialised memory.'),
        ('unknown', 'signature not parsed, check by hand'),
        ('data', 'a zeroed 512 byte buffer'),
        ('none', 'no live use'),
    ])
    for k, d in desc.items():
        if cls_count.get(k):
            w('| %s | %d | %s |' % (k, cls_count[k], d))
    w('')
    if not cls_count.get('struct-x8') and not cls_count.get('unknown'):
        w('No unmapped function returns a struct by value through x8, and every signature was parsed, so the generic trap is')
        w('safe for all of them. If a later change adds one, this script lists it under "struct-x8" and the self-test in')
        w('`macos/MacR17.cpp` must be extended before it can be called.')
        w('')
    odd = [r for r in rows if r['cls'] in ('pod16', 'struct-x8', 'unknown', 'float') or (r['ret'] and '&' in r['ret'])]
    if odd:
        w('Functions with a return type other than void, an integer or a plain pointer:')
        w('')
        w('| hash | name | declared return | class |')
        w('|---|---|---|---|')
        for r in odd:
            w('| %d | %s | `%s` | %s |' % (r['hash'], ', '.join(r['names']), r['ret'] or '', r['cls']))
        w('')
    w('## By feature area')
    w('')
    w('The area is the folder under `src/App` of the files that call the wrapper (or `Red (shared headers)` when only the')
    w('shared headers use it). Script classes are the RTTI classes those files define: their natives are what a script can')
    w('reach.')
    w('')
    w('Reach is by source text and can over-report: for a Codeware wrapper it is every file that names the wrapper (plus')
    w('the declaring header when it uses the wrapper itself); for an SDK function it is every file that names both the')
    w('SDK class and the method.')
    w('')
    for ar in sorted(area_map):
        lst = area_map[ar]
        w('### %s (%d)' % (ar, len(lst)))
        w('')
        cl = sorted({c for r in lst for c in r['classes']})
        if cl:
            w('Script classes in the reaching files: %s.' % ', '.join('`%s`' % c for c in cl))
            w('')
        for r in lst:
            w('- `%s` (%s)%s' % (', '.join(r['names']), r['kind'], (': ' + r['note']) if r['note'] and r['cls'] not in ('void',) else ''))
        w('')
    w('## Every unmapped hash')
    w('')
    w('Status: **not applicable** (proven: there is nothing to call or hook on Mac, reason given), **unreached** (no Codeware code')
    w('reaches it on Mac; it stays a trap), **NEEDED** (Codeware reaches it and it has no row yet).')
    w('')
    w('| hash | name | from | kind | return | wrapper | status | reached from |')
    w('|---|---|---|---|---|---|---|---|')
    status_counts = collections.Counter()
    for r in rows:
        na = next((NOT_APPLICABLE[n] for n in r['names'] if n in NOT_APPLICABLE), None)
        if na:
            status, key = 'not applicable: ' + na, 'not applicable'
        elif r['reach']:
            status, key = '**NEEDED**', 'NEEDED'
        else:
            status, key = 'unreached', 'unreached'
        status_counts[key] += 1
        w('| %d | %s | %s | %s | %s | %s | %s | %s |' % (
            r['hash'], ', '.join('`%s`' % n for n in r['names']), r['origin'], r['kind'],
            ('`%s`' % r['ret']) if r['ret'] else '', ', '.join('`%s`' % s for s in r['symbols'][:2]), status,
            ', '.join(os.path.basename(f) for f in r['reach'][:6]) + (' ...' if len(r['reach']) > 6 else '')))
    w('')
    w('Totals: ' + ', '.join('%s %d' % kv for kv in sorted(status_counts.items())) + '.')
    w('')
    # Address checks (tools/addr-match/check-rows.py writes macos/ADDRESS_CHECK.md; it needs the Windows exe).
    chk = os.path.join(A.ROOT, 'macos', 'ADDRESS_CHECK.md')
    if os.path.exists(chk):
        ctext = A.read(chk)
        rows_line = next((ln for ln in ctext.splitlines() if 'distinct (hash, Mac RVA) rows' in ln), '')
        def counts_of(section):
            part = ctext.split(section)[-1]
            m = re.search(r'Counts: ([^.]*)\.', part.split('\n## ')[0])
            return m.group(1) if m else '?'
        vt_counts = counts_of('## Virtual function slots')
        off_counts = counts_of('## Struct field offsets')
        prop_counts = counts_of('## Properties Codeware adds')
        no_ev = [ln.split('|')[1].strip() for ln in ctext.split('## Struct field offsets')[-1].split('\n## ')[0].splitlines()
                 if ln.startswith('| Raw::') and 'NO-EVIDENCE' in ln]
        w('## Address, vtable and field offset checks')
        w('')
        w('From `macos/ADDRESS_CHECK.md`, generated by `tools/addr-match/check-rows.py` (it needs the Windows exe and')
        w('capstone, so it is not run by the build). It compares every Mac row with its Windows twin and every vtable slot and field')
        w('offset with the evidence tables `tools/addr-match/check-vtable.evidence.tsv`, `check-offsets.evidence.tsv` and')
        w('`check-props.evidence.tsv` (read-only matcher results, each with a Windows function and its Mac twin).')
        w('')
        if rows_line:
            w('- Address rows: ' + rows_line.strip())
        w('- Virtual function slots (`Core::RawVFunc`, the Apple side of the `#if` blocks): ' + vt_counts + '. A binding is only called on Mac when it is marked')
        w('  verified; several are not Windows + 8 (journal GetEntryByHash and ChangeEntryState, community GetCommunity and GetSpawner,')
        w('  mappin GetPoiMappinPhase), and the struct-return ones have x8 adapters.')
        w('- Struct field offsets (`Core::OffsetPtr` in `src/Red`): ' + off_counts + '. Mac differs from Windows for the mappin journal hash (0x88),')
        w('  the workspot lock (0x4C) and the workspot instance map (0x68). Open (no Windows/Mac twin yet, checked in game): ' + (', '.join('`%s`' % n for n in no_ev) or 'none') + '.')
        w('- Properties Codeware adds to game classes by offset (`RTTI_PROPERTY`): ' + prop_counts + '. The reflection dump holds them at Codeware\'s own')
        w('  offsets, so each was checked against the game\'s code; `entSkinnedMeshComponent.meshResource` is 0x1F8 on Mac, not 0x200.')
        w('')
    # Hand-marked Windows-only paths: a source line "MAC-NOT-YET: text" in a comment.
    marks = []
    for rel in sorted(src_texts):
        raw = A.read(os.path.join(A.ROOT, rel))
        for i, line in enumerate(raw.splitlines(), 1):
            m = re.search(r'MAC-NOT-YET:\s*(.+)', line)
            if m:
                marks.append((rel, i, m.group(1).strip()))
    for sub in ('macos',):
        for p in A.walk_sources(os.path.join(A.ROOT, sub)):
            rel = os.path.relpath(p, A.ROOT)
            for i, line in enumerate(A.read(p).splitlines(), 1):
                m = re.search(r'MAC-NOT-YET:\s*(.+)', line)
                if m:
                    marks.append((rel, i, m.group(1).strip()))
    w('## Windows-only code paths behind guards')
    w('')
    if marks:
        w('Marked in the sources with a `MAC-NOT-YET:` comment.')
        w('')
        w('| file | line | what |')
        w('|---|---|---|')
        for rel, i, t in marks:
            w('| %s | %d | %s |' % (rel, i, t))
    else:
        w('None marked yet.')
    w('')
    notes = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'not-yet-notes.md')
    if os.path.exists(notes):
        w('<!-- the following sections are hand-written in tools/mac/not-yet-notes.md -->')
        w('')
        for line in open(notes).read().rstrip('\n').split('\n'):
            w(line)
        w('')
    w('## Upstream (Windows) findings')
    w('')
    w('Found while checking the Mac port against the 2.3.1 executable (Steam build 20383525). They are candidates for an upstream')
    w('issue; the Windows values in this fork are NOT changed, and whether to file an issue is decided at publish time.')
    w('')
    w('1. **`Raw::MappinSystem::GetPoiMappinPhase` uses vtable offset 0x3C8; the function that reads the phase is at 0x430.** In the')
    w('   2.3.1 Windows executable the slots 0x3C0 and 0x3C8 of `gamemappinsIMappinSystem` are flag-setter thunks (`movzx r9d,r8b;')
    w('   mov r8b,1|2; jmp 0x1D1C650`, they lock this+0x168 and set a bit on a mappin). The slot that returns the phase is 0x430')
    w('   (Windows 0x695EC8: map lookup on this+0x110, default result 5). Evidence: the body, and the game call site Windows 0x695C88')
    w('   that calls `[rcx+0x430]` and compares the result with 5, with its Mac twin 0x2F09618 (`[x8,#0x438]`, `cmp w0,#5`). The Mac')
    w('   binding uses 0x438. The R21 read-only matcher found it; the Windows 0x3C8 may be right for another game build.')
    w('2. **The slot comments in the SDK headers for `gameIDynamicEntityIDSystem`, `gameIPopulationSystem` and `gameIPersistencySystem`')
    w('   are 8 too low.** They start the first derived virtual at 0x1A8, but `IGameSystem` already ends with `OnUninitialize` at 0x1A8')
    w('   (it declares `OnInitialize` at 0x1A0), so the first derived virtual is Windows 0x1B0. Checked in all three Windows vtables:')
    w('   `OnUninitialize` is at 0x1A8. The slots the compiler uses are right (they come from declaration order); only the comments')
    w('   mislead anyone who binds a virtual by number. Example: `IPersistencySystem::GetPersistentState` is Windows 0x1B0 (0x217908),')
    w('   comment 0x1A8.')
    w('3. **Two rows of the Windows address table point at the wrong function.** `VehicleGarageComponent_LoadSummonSetup` (hash')
    w('   1159928678, table value 0x126DF78) is a static RTTI type getter; the function that reads the `Vehicle.summon_setup` flats is')
    w('   0x126BF78 (0x2000 lower). `CNamePool_AddCString` (hash 4292220681, table value 0x2228C98) is an unrelated vtable slot (a')
    w('   `HasName`-like method of another class); the SDK function it names is inlined in the executable (CString to StringView, then the')
    w('   name adder at Windows 0x28A6CC), so no row is correct for that hash.')
    w('')
    with open(a.out, 'w') as f:
        f.write('\n'.join(L) + '\n')
    print('wrote %s: %d hashes, %d mapped, %d unmapped (%s)' % (a.out, total, mapped_here, unmapped,
                                                                 ', '.join('%s=%d' % kv for kv in sorted(cls_count.items()))))


if __name__ == '__main__':
    main()
