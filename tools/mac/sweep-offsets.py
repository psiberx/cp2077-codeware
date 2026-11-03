#!/usr/bin/env python3
"""Compare SDK header member offsets (the // HEX comments) with the game's reflected property offsets on Mac.

The reflection TSV comes from the plugin: run a session with CODEWARE_MAC_DIAG=1 and
CODEWARE_MAC_DUMP_REFLECTION=/tmp/cw-reflection.tsv (macos/MacR20.cpp, DumpReflection). The Windows-derived SDK headers pad to
the Windows offsets; clang's Itanium layout reuses the tail padding of non-POD base classes, so members of many derived classes sit
4 or 8 bytes lower in the Mac game (r20a: inkWidgetLibraryResource.externalLibraries 0x50, SDK 0x58).

usage: sweep-offsets.py <reflection.tsv> [sdk include dir]"""
import os, re, sys, collections
tsv = sys.argv[1]
sdk = sys.argv[2] if len(sys.argv) > 2 else os.path.expanduser('~/repos/cp2077-mac/RED4ext.SDK-macos/include/RED4ext')
mac = {}      # (class, prop) -> offset
size = {}
for l in open(tsv):
    p = l.rstrip('\n').split('\t')
    if p[0] == 'P':
        mac[(p[1], p[2])] = int(p[3])
    elif p[0] == 'C':
        size[p[1]] = int(p[3])
name_re = re.compile(r'static constexpr const char\* NAME = "([^"]+)"')
mem_re = re.compile(r'^\s+[\w:<>,\s\*&]+?\s+(\w+)(?:\[[^\]]*\])?;\s*//\s*([0-9A-Fa-f]+)\s*$')
res = collections.defaultdict(list)
checked = 0; same = 0
for root, _, files in os.walk(sdk):
    for f in files:
        if not f.endswith('.hpp'): continue
        cur = None
        for line in open(os.path.join(root, f), errors='replace'):
            m = name_re.search(line)
            if m:
                cur = m.group(1); continue
            if cur is None: continue
            m = mem_re.match(line)
            if m:
                prop, off = m.group(1), int(m.group(2), 16)
                if prop.startswith('unk'): continue
                key = (cur, prop)
                if key in mac:
                    checked += 1
                    if mac[key] == off: same += 1
                    else: res[cur].append((prop, off, mac[key]))
print('compared %d members, %d equal, %d different in %d classes' % (checked, same, checked - same, len(res)))
for cls in sorted(res):
    print(cls, ' '.join('%s sdk=%#x game=%#x' % x for x in res[cls]))
