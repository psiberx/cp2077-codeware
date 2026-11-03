#!/usr/bin/env python3
"""gen-mac-layout.py: make the RED4ext SDK struct layouts match the Mac game, and guard them at build time.

Why: the SDK headers are generated from the Windows game (MSVC layout, explicit `unkNN` pads to the Windows offsets). The Mac game is
built with clang (Itanium layout), which puts the first member of a derived class into the tail padding of a non-POD base. Members of
about 360 classes (and everything derived from them) sit 4 or 8 bytes lower than the header says (r20a: inkWidgetLibraryResource
.externalLibraries 0x50, header 0x58). Fix: an Apple-only branch laid out from the game's own reflection dump.

Inputs: the reflection dump of the running game (CODEWARE_MAC_DIAG=1 CODEWARE_MAC_DUMP_REFLECTION=<file>, macos/MacR20.cpp), the SDK
include dir. Modes:
  --report            counts only
  --apply             rewrite the SDK headers in place (each affected struct gets `#if defined(__APPLE__) ... #else <original> #endif`)
  --guard <out.cpp>   write the build-time guard: static_assert(offsetof/sizeof) for every reflected member of every SDK class
Classes: shifted = some member offset differs from the header. Full rewrite = shifted classes and everything derived from a changed
class (their start offset depends on the base). Tail-only = ancestors with a trailing `unkNN` pad: on Apple the pad is dropped so that
derived members can use the tail padding (the class size stays the same through alignment). Hand-written structs with members the
game does not reflect are listed for manual treatment (MANUAL), nothing is generated for them.

Usage: gen-mac-layout.py --dump /tmp/cw-reflection.tsv [--sdk <include/RED4ext>] [--apply] [--guard macos/MacLayoutGuard.cpp]
"""
import argparse, collections, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import sdkparse

# SDK members the game reflects under another name: (SDK struct, SDK member) -> reflected property. The guard checks them against it.
SDK_ALIASES = {
    ('CMeshMaterialEntry', 'materialWeak'): 'material',      # the weak handle at 0 is the reflected "material"
}
# SDK members whose name is reflected on a different member, so they are not compared by name.
# Properties that Codeware itself adds to game classes by offset (RTTI_EXPAND_CLASS ... RTTI_PROPERTY(type, offset, name)). The dump holds them
# at Codeware's Windows offsets, so they say nothing about the game: never use them as layout evidence.
CODEWARE_PROPS = {
    ('entMeshComponent', 'meshResource'), ('entSkinnedMeshComponent', 'meshResource'), ('inkActionName', 'action'),
    ('worldInstancedMeshNode', 'boundingBoxes'), ('worldInstancedMeshNode', 'streamingDistances'),
    ('worldInstancedMeshNode', 'instanceBatches'), ('workWorkspotInstance', 'tree'), ('workWorkspotInstance', 'resource'),
    ('workWorkspotInstance', 'animName'), ('workWorkspotInstance', 'idleAnim'), ('workWorkspotInstance', 'entryId'),
    ('graphGraphSocketDefinition', 'owner'), ('audioDialogLineEventData', 'gender'),
}

# Offsets of unreflected SDK members, verified in the game's code by a Windows/Mac function twin: (qualified class, member, Mac offset, evidence).
MANUAL_ASSERTS = [
    ('RED4ext::ent::SkinnedMeshComponent', 'meshHandle', 0x200, 'Windows 0x1B3B5C reads [this+0x200], Mac 2.5.0 twin 0x198FDA0 reads [this+0x200] (2.3.1: 0xC7D688, +0x1F8)'),
]

SDK_SKIP = {
    ('CMeshMaterialEntry', 'material'),
    # Unreflected members of hand-written headers whose Mac position is not established: Codeware reaches the mesh through the
    # reflected meshResource / morphResource instead (ComponentWrapper.cpp). Do not use them on Mac.
    ('SkinnedMeshComponent', 'renderProxy'), ('SkinnedMeshComponent', 'appearanceHandle'), ('SkinnedMeshComponent', 'meshHandle'),
    ('MorphTargetSkinnedMeshComponent', 'renderProxy'), ('MorphTargetSkinnedMeshComponent', 'meshHandle'),
}

# Classes whose sizeof the plugin depends on (it derives from them or allocates them); filled from the plugin sources by --size-classes.
SIZE_CLASSES = set()
MARK = '// mac-layout (generated from the reflection dump)'

def load_dump(path):
    cls, props = {}, collections.defaultdict(dict)
    for l in open(path):
        p = l.rstrip('\n').split('\t')
        if p[0] == 'C':
            cls[p[1]] = dict(parent=p[2], size=int(p[3]), holder=int(p[4]), align=int(p[5]))
        elif p[0] == 'P':
            props[p[1]][p[2]] = (int(p[3]), p[4])
    return cls, props

def reflect_prop(props, r, name):
    """The reflected property for an SDK member name (the SDK adds a trailing underscore to reserved words)."""
    p = props[r]
    if (r, name) in CODEWARE_PROPS or (r, name[:-1] if name.endswith('_') else name) in CODEWARE_PROPS: return None
    if name in p: return name
    if name.endswith('_') and name[:-1] in p: return name[:-1]
    return None

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dump', required=True)
    ap.add_argument('--sdk', default=os.path.expanduser('~/repos/cp2077-mac/RED4ext.SDK-macos/include/RED4ext'))
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--guard')
    ap.add_argument('--failing', help='compiler output of the guard: classes with a failing offsetof assertion are added to the rewrite set (the header comments can agree with the game while the compiled layout does not)')
    ap.add_argument('--size-classes', help='file with SDK class names (one per line) whose sizeof is asserted')
    ap.add_argument('--sources', nargs='*', default=[], help='plugin source dirs scanned for #include <RED4ext/...> lines outside the pch; those headers are guarded too')
    ap.add_argument('--pch', help='the plugin precompiled header (src/pch.hpp): the guard covers the SDK headers it includes, so it only contains classes that compile in the plugin')
    ap.add_argument('--cflags', default='', help='compiler flags (includes, defines) of the plugin build, used to list the headers of --pch')
    a = ap.parse_args()
    cls, props = load_dump(a.dump)
    if a.size_classes:
        SIZE_CLASSES.update(x.strip() for x in open(a.size_classes) if x.strip())

    structs = []
    for path in sdkparse.walk(a.sdk):
        for st in sdkparse.parse_file(path):
            st['reflect'] = sdkparse.reflect_name(st)
            lines = st['text'].split('\n')
            ms = sdkparse.members(st)
            for m in ms:
                if m['kind'] in ('member', 'pad'):
                    mm = re.search(r'//\s*([0-9A-Fa-f]+)\s*$', lines[m['line']])
                    m['win'] = int(mm.group(1), 16) if mm else None
            st['members'] = ms
            st['data'] = [m for m in ms if m['kind'] in ('member', 'pad')]
            body = st['text'][st['body_start']:st['body_end']]
            st['marked'] = MARK in body or '#if defined(__APPLE__)' in body or '#if !defined(__APPLE__)' in body
            structs.append(st)

    def bases(st):
        if not st['bases']: return []
        out = []
        for b in st['bases'].split(','):
            b = b.strip()
            if b.startswith(('public ', 'private ', 'protected ')): b = b.split(None, 1)[1]
            out.append(b)
        return out
    short = collections.defaultdict(list)
    for st in structs: short[st['name']].append(st)
    def base_structs(st):
        res = []
        for b in bases(st):
            b = b.split('<')[0].strip()
            cands = short.get(b.split('::')[-1], [])
            if len(cands) > 1:
                # R25. Several SDK structs share the short name (quest::NodeDefinition and game::interactions::NodeDefinition): pick the one the
                # base clause names (qualified), or the one in the namespace of the derived struct (unqualified).
                if '::' in b:
                    exact = [c for c in cands if sdkparse.qualified(c).endswith('::' + b.lstrip(':')) or sdkparse.qualified(c) == b.lstrip(':')]
                else:
                    exact = [c for c in cands if c['ns'] == st['ns']]
                if len(exact) == 1: cands = exact
            res.extend(cands)
        return res
    children = collections.defaultdict(list)
    for st in structs:
        for b in base_structs(st): children[id(b)].append(st)

    def shifted(st):
        r = st['reflect']
        if not r or r not in cls: return False
        for m in st['data']:
            if m['kind'] != 'member' or m.get('win') is None: continue
            pn = reflect_prop(props, r, m['name'])
            if pn and props[r][pn][0] != m['win']: return True
        return False
    def tail_pad(st):
        return bool(st['data']) and st['data'][-1]['kind'] == 'pad'

    def descendants(st):
        out, stack, seen = [], [st], {id(st)}
        while stack:
            for c in children[id(stack.pop())]:
                if id(c) not in seen:
                    seen.add(id(c)); out.append(c); stack.append(c)
        return out
    def data_bound(st, lower=0):
        """Lowest offset >= lower at which the data of a descendant of st starts (the game reuses st's tail padding up to there), or None.
        Only members the SDK declares in the descendants count, at their reflected (Mac) offsets: the dump also holds the properties of
        redscript classes, whose offsets are relative to a script holder and say nothing about the native layout, and properties the game
        reflects on a derived class while the SDK keeps the member in st (questPuppetNodeType)."""
        low = None
        for d in descendants(st):
            r = d['reflect']
            if not r or r not in cls: continue
            for m in d['data']:
                if m['kind'] != 'member': continue
                pn = reflect_prop(props, r, m['name'])
                if not pn: continue
                o = props[r][pn][0]
                if o >= lower and (low is None or o < low): low = o
        return low

    failing = set()
    if a.failing:
        for l in open(a.failing, errors='replace'):
            m = re.search(r"requirement '__builtin_offsetof\(([^,]+), (\w+)\) == ", l)
            if m: failing.add(m.group(1))
    full, tail = set(), set()
    queue = []
    for st in structs:
        if shifted(st) or sdkparse.qualified(st) in failing:
            full.add(id(st)); queue.append(st)
    while queue:
        st = queue.pop()
        for c in children[id(st)]:
            if id(c) not in full:
                full.add(id(c)); tail.discard(id(c)); queue.append(c)
        for p in base_structs(st):
            # R25. Walk up through classes with no data members of their own (an empty subclass such as game::data::ValueDataNode): the
            # first data member of a derived class starts in the tail padding of the nearest ancestor that has data. Stopping at the
            # immediate base left DataNode, the quest NodeDefinition chain and others with their Windows tail, and 39 derived headers
            # with a negative padding array. The empty classes themselves are not marked: only a tail that is dropped drags its
            # descendants into the rewrite.
            q = p
            while q is not None and id(q) not in tail:
                if tail_pad(q) and id(q) not in full:
                    tail.add(id(q)); queue.append(q)
                    break
                if q['data']: break      # a rewritten class (full) drops its own pads; a class that ends in a real member has none
                bq = base_structs(q)
                q = bq[0] if len(bq) == 1 else None
    print('structs %d, reflected %d, shifted %d, failing in the guard %d, full rewrite %d, tail-only %d' % (
        len(structs), sum(1 for s in structs if s['reflect'] in cls), sum(1 for s in structs if shifted(s)), len(failing), len(full), len(tail)))

    edits = collections.defaultdict(list)   # path -> (lo, hi, kind, lines)
    manual = []

    def tail_edit(st):
        """The edit for the trailing pad of st (one or more consecutive pad lines at the end of its data), or None when nothing is needed.
        R25. The pad is kept up to the lowest offset where a descendant stores data (the game reuses the tail only from there on), so that
        sizeof(st) stays what the game has instead of dropping the whole pad. A class without a base class is plain data to clang (the vptr of
        the game's class is an opaque head here) and clang never reuses the tail of such a class: a user-provided destructor makes it non-POD,
        as it is in the game."""
        data = st['data']
        if not data or data[-1]['kind'] != 'pad': return None
        hi = data[-1]['line']; lo = hi
        k = len(data) - 1
        while k > 0 and data[k - 1]['kind'] == 'pad' and data[k - 1]['line'] == lo - 1:
            k -= 1; lo = data[k]['line']
        lines0 = st['text'].split('\n')
        pad_start = data[k].get('win')
        pm = re.search(r'\[\s*0x([0-9A-Fa-f]+)\s*-', lines0[hi])
        pad_end = int(pm.group(1), 16) if pm else None
        if pad_start is None or pad_end is None:
            return (lo, hi, 'tail', None, st['name'])
        bound = data_bound(st, pad_start)
        if bound is None or bound >= pad_end:
            return None                       # no descendant stores data in the pad: the Windows tail is right
        new = []
        if bound > pad_start:
            new.append('    uint8_t unk%X[0x%X - 0x%X]; // %X' % (pad_start, bound, pad_start, pad_start))
        if not st['bases']:
            new.append('    ~%s() {} // non-POD, so clang reuses the tail padding like the game' % st['name'])
        return (lo, hi, 'tailtrim', new, st['name'])

    for st in structs:
        if id(st) in tail:
            if st['marked']: continue
            e = tail_edit(st)
            if e: edits[st['path']].append(e)
        elif id(st) in full:
            if st['marked']: continue
            r = st['reflect']
            if r not in cls: manual.append((st['name'], 'no dump entry')); continue
            data = st['data']
            if not data: continue
            named = [m for m in data if m['kind'] == 'member']
            if not named:
                # R25. A class whose only data is a trailing pad (ent::IComponent derived ICharacterCustomizationComponent): its derived
                # classes can start inside the pad, so trim it like a tail.
                e = tail_edit(st)
                if e: edits[st['path']].append(e)
                continue
            bad = [m['name'] for m in named if reflect_prop(props, r, m['name']) is None]
            if bad: manual.append((st['name'], 'unreflected named members %s' % bad, st['path'])); continue
            bs = bases(st)
            if len(bs) > 1: manual.append((st['name'], 'several bases')); continue
            offs = [props[r][reflect_prop(props, r, m['name'])][0] for m in named]
            if offs != sorted(offs): manual.append((st['name'], 'members not in offset order')); continue
            if any(m['kind'] == 'other' and data[0]['line'] < m['line'] < data[-1]['line'] for m in st['members']):
                manual.append((st['name'], 'other lines inside the member region')); continue
            new = [MARK]
            prev, prev_off = None, None
            for m, off in zip(named, offs):
                if prev is None:
                    if bs: new.append('    uint8_t unk_%X[0x%X - ::RED4ext::Detail::DataSize<%s>];' % (off, off, bs[0]))
                    elif off: new.append('    uint8_t unk_%X[0x%X];' % (off, off))
                else:
                    new.append('    uint8_t unk_%X[0x%X - (0x%X + sizeof(%s))];' % (off, off, prev_off, prev['name']))
                new.append('    %s %s%s; // %X' % (m['type'], m['name'], m['array'] or '', off))
                prev, prev_off = m, off
            edits[st['path']].append((data[0]['line'], data[-1]['line'], 'full', new, st['name']))

    kinds = collections.Counter(e[2] for v in edits.values() for e in v)
    print('edits: %d structs in %d files (%s); manual: %d' % (sum(len(v) for v in edits.values()), len(edits), ', '.join('%s %d' % kv for kv in sorted(kinds.items())), len(manual)))
    for path, lst in edits.items():
        for e in lst:
            if e[2] in ('tail', 'tailtrim'): print('  TAIL', e[2], e[4], os.path.relpath(path, a.sdk), '|'.join(x.strip() for x in (e[3] or [])))
    for m in manual: print('  MANUAL', m[0], '-', m[1])

    if a.apply:
        for path, lst in edits.items():
            lines = open(path).read().split('\n')
            for lo, hi, kind, new, name in sorted(lst, key=lambda x: -x[0]):
                orig = lines[lo:hi + 1]
                if kind == 'tail':
                    repl = ['#if !defined(__APPLE__)'] + orig + ['#endif // the game reuses this tail padding (see Detail::DataSize)']
                elif kind == 'tailtrim':
                    repl = ['#if defined(__APPLE__)'] + new + ['#else'] + orig + ['#endif // the game reuses this tail padding (see Detail::DataSize)']
                else:
                    repl = ['#if defined(__APPLE__)'] + new + ['#else'] + orig + ['#endif']
                lines[lo:hi + 1] = repl
            open(path, 'w').write('\n'.join(lines))
        print('applied')

    if a.guard:
        import shlex, subprocess
        sdkroot = os.path.dirname(a.sdk)        # .../include
        reach = None
        extra_incl = []
        if a.pch:
            cmd = ['clang++', '-std=gnu++20', '-arch', 'arm64', '-fno-rtti', '-fsyntax-only', '-H', '-w'] + shlex.split(a.cflags) + [a.pch]
            p = subprocess.run(cmd, capture_output=True, text=True)
            reach = set()
            for l in p.stderr.split('\n'):
                m = re.match(r'^\.+ (.*)$', l)
                if m and os.path.abspath(m.group(1)).startswith(os.path.abspath(sdkroot) + '/'):
                    reach.add(os.path.relpath(os.path.abspath(m.group(1)), sdkroot))
            extra = set()
            for d in a.sources:
                for root, _, files in os.walk(d):
                    for f in files:
                        if f.endswith(('.cpp', '.hpp', '.mm', '.h', '.inc')):
                            for l in open(os.path.join(root, f), errors='replace'):
                                m = re.match(r'\s*#\s*include\s*<(RED4ext/[^>]+)>', l)
                                if m and os.path.exists(os.path.join(sdkroot, m.group(1))): extra.add(m.group(1))
            if extra:
                # the closure of those headers as well (they may pull in more)
                tu = '\n'.join('#include <%s>' % e for e in sorted(extra))
                p2 = subprocess.run(['clang++', '-std=gnu++20', '-arch', 'arm64', '-fno-rtti', '-fsyntax-only', '-H', '-w'] + shlex.split(a.cflags) + ['-x', 'c++', '-'], input=tu, capture_output=True, text=True)
                for l in p2.stderr.split('\n'):
                    m = re.match(r'^\.+ (.*)$', l)
                    if m and os.path.abspath(m.group(1)).startswith(os.path.abspath(sdkroot) + '/'):
                        reach.add(os.path.relpath(os.path.abspath(m.group(1)), sdkroot))
                extra_incl = sorted(extra)
            print('headers reached from %s (+%d plugin includes): %d (SDK)' % (a.pch, len(extra), len(reach)))
        incl, asserts = set(), []
        nm = ns = 0
        for st in structs:
            r = st['reflect']
            if not r or r not in cls: continue
            q = sdkparse.qualified(st)
            rel = os.path.relpath(st['path'], sdkroot)
            if reach is not None and rel not in reach: continue
            incl.add(rel)
            for m in st['data']:
                if m['kind'] != 'member': continue
                key = (st['name'], m['name'])
                if key in SDK_SKIP: continue
                pn = SDK_ALIASES.get(key) or reflect_prop(props, r, m['name'])
                if not pn or pn not in props[r]: continue
                asserts.append('static_assert(__builtin_offsetof(%s, %s) == 0x%X, "%s::%s");' % (q, m['name'], props[r][pn][0], q, m['name']))
                nm += 1
            if st['reflect'] in SIZE_CLASSES:
                asserts.append('static_assert(sizeof(%s) == %d, "sizeof(%s)");' % (q, cls[r]['size'], q)); ns += 1
        # Members the game does not reflect (so the dump cannot check them) whose Mac offset was verified in the game's code by a
        # Windows/Mac function twin. The dump also holds properties that Codeware itself registers at the Windows offsets (see
        # CODEWARE_PROPS); they are never evidence and are not asserted from the dump.
        for cq, cm, co, why in MANUAL_ASSERTS:
            asserts.append('static_assert(__builtin_offsetof(%s, %s) == 0x%X, "%s::%s: %s");' % (cq, cm, co, cq, cm, why))
        with open(a.guard, 'w') as f:
            f.write('// Generated by tools/mac/gen-mac-layout.py from the reflection dump of the Mac game. Do not edit.\n')
            f.write('// Every reflected member of every SDK class the plugin sees: the compiled offset must equal the game\'s. A wrong\n')
            f.write('// layout fails the build, not the game. Sizes are checked for the classes the plugin derives from or instantiates.\n')
            f.write('#include "%s"\n' % (os.path.basename(a.pch) if a.pch else 'RED4ext/RED4ext.hpp'))
            for e in (extra_incl if a.pch else []): f.write('#include <%s>\n' % e)
            f.write('#pragma clang diagnostic ignored "-Winvalid-offsetof"\n')
            f.write('\n'.join(asserts) + '\n')
        print('guard: %d classes, %d member asserts, %d size asserts' % (len(incl), nm, ns))

main()
