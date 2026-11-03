#!/usr/bin/env python3
"""Compose Codeware's redscript sources into one file per module. A Python port of tools/dist/steps/compose-redscripts.ps1.

For every .reds file under <scripts-dir>:
  * module   the first line that starts (at column 0) with "module <name>"; the file belongs to that module's bundle,
             a file without one goes to the global bundle "<Project>.Global"
  * imports  every line that starts with "import <name>"; the bundle keeps each import once
  * source   every other line, except comment lines ("//" after optional spaces) and blank lines
Each bundle is written to <out-dir>/<scope>.reds:
  // <Project> <Version>
  module <Module>            (module bundles only)
  import <Import>            (one line each, sorted)
  <blank line><source of file 1><blank line><source of file 2> ...
The Windows script writes the same file with ASCII encoding (anything else becomes '?'). Files are visited like
Get-ChildItem -Recurse: the files of a folder first, in name order, then its sub folders.

Usage: compose-redscripts.py <out-dir> [--scripts <scripts-dir>] [--project Codeware] [--version 1.20.4]
Prints one line per bundle. The default scripts folder is ../scripts next to this tool.
"""
import argparse
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

MODULE_RE = re.compile(r'^module\s+(.+)', re.I)
IMPORT_RE = re.compile(r'^import\s+(.+)', re.I)
SKIP_RE = re.compile(r'^\s*(//|module\s|import\s)', re.I)
BLANK_RE = re.compile(r'^\s*$')


def walk(top):
    """Files of a folder first (name order), then the sub folders, like Get-ChildItem -Recurse."""
    entries = sorted(os.listdir(top), key=str.lower)
    files = [e for e in entries if os.path.isfile(os.path.join(top, e))]
    dirs = [e for e in entries if os.path.isdir(os.path.join(top, e))]
    for f in files:
        yield os.path.join(top, f)
    for d in dirs:
        yield from walk(os.path.join(top, d))


def default_version():
    for rel in ('src/App/Project.hpp', 'macos/build/generated/App/Project.hpp'):
        p = os.path.join(ROOT, rel)
        if os.path.exists(p):
            m = re.search(r'"(\d+\.\d+\.\d+)"', open(p, errors='replace').read())
            if m:
                return m.group(1)
    m = re.search(r'set_version\("(\d+\.\d+\.\d+)"', open(os.path.join(ROOT, 'xmake.lua')).read())
    return m.group(1) if m else '0.0.0'


def compose(scripts_dir, project, version, exclude=()):
    """Returns {scope: text}. exclude: file paths relative to scripts_dir that are left out."""
    exclude = {e.replace(os.sep, "/") for e in exclude}
    global_scope = project + '.Global'
    bundles = {}
    for path in walk(scripts_dir):
        if not path.endswith('.reds'):
            continue
        if os.path.relpath(path, scripts_dir).replace(os.sep, '/') in exclude:
            continue
        with open(path, errors='replace') as f:
            lines = f.read().splitlines()
        module = next((m.group(1) for m in map(MODULE_RE.match, lines) if m), None)
        imports = [m.group(1) for m in map(IMPORT_RE.match, lines) if m]
        source = [ln for ln in lines if not SKIP_RE.match(ln) and not BLANK_RE.match(ln)]
        text = '\n'.join(source).strip()
        scope = module.rstrip() if module else global_scope
        bundle = bundles.setdefault(scope, dict(module=module.rstrip() if module else None, imports={}, sources=[]))
        bundle['sources'].append(text)
        for imp in imports:
            bundle['imports'][imp] = 1

    out = {}
    for scope, b in bundles.items():
        parts = ['// %s %s\n' % (project, version)]
        if b['module']:
            parts.append('module %s\n' % b['module'])
        for imp in sorted(b['imports']):
            parts.append('import %s\n' % imp)
        for src in b['sources']:
            if src:
                parts.append('\n%s\n' % src)
        out[scope] = ''.join(parts)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('out_dir')
    ap.add_argument('--scripts', default=os.path.join(ROOT, 'scripts'))
    ap.add_argument('--project', default='Codeware')
    ap.add_argument('--version', default=None)
    ap.add_argument('--exclude', default=None, help='file with script paths (relative to --scripts) to leave out, one per line')
    a = ap.parse_args()

    version = a.version or default_version()
    excl = []
    if a.exclude and os.path.exists(a.exclude):
        excl = [l.split('#', 1)[0].strip() for l in open(a.exclude) if l.split('#', 1)[0].strip()]
    bundles = compose(a.scripts, a.project, version, excl)
    os.makedirs(a.out_dir, exist_ok=True)
    for scope in sorted(bundles):
        data = bundles[scope].encode('ascii', 'replace')
        path = os.path.join(a.out_dir, scope + '.reds')
        with open(path, 'wb') as f:
            f.write(data)
        print('%s: %d bytes' % (path, len(data)))
    if not bundles:
        print('no .reds files under %s' % a.scripts, file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
