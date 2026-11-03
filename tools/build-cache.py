#!/usr/bin/env python3
"""Build a redscript cache for the macOS game from the whole mod set, outside the game folder.

Usage: build-cache.py <game-dir> <out-cache> [--staging DIR] [--base-cache FILE] [--exclude FILE] [--plugin-scripts NAME=DIR ...]
                      [--compose-scripts NAME=DIR[@VERSION] ...] [--extra-scripts DIR|''] [--dry-run]

--dry-run stages the inputs and prints the fingerprint of the cache that would be built ("FINGERPRINT=<sha256>": the input files and the
base cache), without compiling and without writing <out-cache>. The everyday launcher compares it with the fingerprint of the installed
cache and recompiles only when it differs.

What goes into the staging tree <staging>/r6 (never the game folder):
  cache/final.redscripts   the base cache: a copy of <game>/r6/cache/final.redscripts.working-nolezzie (the stock
                           script cache; its sha256 is checked against the one the Phase 6 launcher restores)
  scripts/Codeware/        Codeware's own scripts, composed like the Windows package (tools/compose-redscripts.py)
  scripts/<Mod>/           every other folder of <game>/r6/scripts (Equipment-EX, Lizzie's BDs, ...)
  scripts/<Plugin>/        <game>/red4ext/plugins/<Plugin>/Scripts of each plugin (ArchiveXL, TweakXL, ...); with
                           --plugin-scripts NAME=DIR the folder DIR is used for that plugin instead (for example the scripts/
                           folder of a source-built ArchiveXL, so the cache matches the plugin that is loaded)
  scripts/CodewareMacDiag/ tools/diag-scripts (macOS self-test classes, --extra-scripts)
A path listed in the exclude file (default tools/build-cache.exclude, one path per line, '#' starts a comment) is left out;
every exclusion is recorded in the manifest. A line `Codeware-src/<path under scripts/>` leaves that Codeware source file
out of the composition; any other line is a staging-relative path (for example `LizziesBDs/Audio.reds`).

The compile goes through ~/repos/cp2077-mac/tools/scc_nopopup.py ONLY (engine/tools/scc shows a modal alert on every
failed compile). Outputs:
  <out-cache>                  the cache, only when the compile succeeded
  <out-cache>.manifest.json    sha256 of every input file, the base cache, the composed Codeware bundles, the result
  <out-cache>.errors.txt       the compiler's error text and the error lines of the log, empty on success
Exit code: 0 compiled, 1 compile errors, 2 usage or input problem.
"""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import importlib.util  # noqa: E402

_spec = importlib.util.spec_from_file_location('compose_redscripts', os.path.join(HERE, 'compose-redscripts.py'))
compose_mod = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(compose_mod)

STOCK_CACHE_SHA256 = '9a5579067ef2e3fc0f959da615ec6a0765b4bf0958abf47807791321a4dc7937'
SCC = os.path.expanduser('~/repos/cp2077-mac/tools/scc_nopopup.py')


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, 'rb') as f:
        for chunk in iter(lambda: f.read(1 << 20), b''):
            h.update(chunk)
    return h.hexdigest()


def read_excludes(path):
    out = set()
    if path and os.path.exists(path):
        for line in open(path):
            line = line.split('#', 1)[0].strip()
            if line:
                out.add(line.replace('\\', '/'))
    return out


def copy_tree(src, dst, rel_base, excludes, inputs, excluded, source_label):
    for dp, dn, fn in os.walk(src):
        dn.sort()
        for name in sorted(fn):
            if name.startswith('.'):
                continue
            s = os.path.join(dp, name)
            rel = os.path.join(rel_base, os.path.relpath(s, src)).replace(os.sep, '/')
            if rel in excludes:
                excluded.append(rel)
                continue
            d = os.path.join(dst, os.path.relpath(s, src))
            os.makedirs(os.path.dirname(d), exist_ok=True)
            shutil.copyfile(s, d)
            inputs.append({'path': rel, 'sha256': sha256_file(s), 'source': source_label})


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('game_dir')
    ap.add_argument('out_cache')
    ap.add_argument('--staging', default=os.path.expanduser('~/repos/cp2077-mac/scripts-full/staging'))
    ap.add_argument('--base-cache', default=None)
    ap.add_argument('--exclude', default=os.path.join(HERE, 'build-cache.exclude'))
    ap.add_argument('--codeware-scripts', default=os.path.join(os.path.dirname(HERE), 'scripts'))
    ap.add_argument('--plugin-scripts', action='append', default=[], metavar='NAME=DIR',
                    help='use DIR instead of <game>/red4ext/plugins/NAME/Scripts for that plugin (repeatable)')
    ap.add_argument('--compose-scripts', action='append', default=[], metavar='NAME=DIR[@VERSION]',
                    help='compose the plugin sources in DIR into one file per module, like the Windows package does (the same composition as '
                         'Codeware\'s), and stage them as scripts/NAME; replaces that plugin\'s Scripts folder (repeatable)')
    ap.add_argument('--extra-scripts', default=os.path.join(HERE, 'diag-scripts'),
                    help='macOS self-test scripts (tools/diag-scripts), staged as scripts/CodewareMacDiag; pass an empty string to leave them out')
    ap.add_argument('--dry-run', action='store_true', help='stage the inputs, print FINGERPRINT=<sha256> and exit without compiling')
    a = ap.parse_args()

    game = os.path.abspath(a.game_dir)
    out_cache = os.path.abspath(a.out_cache)
    staging = os.path.abspath(a.staging)
    if staging.startswith(game + os.sep) or out_cache.startswith(game + os.sep):
        print('build-cache: the staging tree and the output must be outside the game folder', file=sys.stderr)
        return 2
    base = a.base_cache or os.path.join(game, 'r6', 'cache', 'final.redscripts.working-nolezzie')
    if not os.path.isfile(base):
        print('build-cache: base cache not found: %s' % base, file=sys.stderr)
        return 2
    if not os.path.isfile(SCC):
        print('build-cache: %s not found' % SCC, file=sys.stderr)
        return 2

    base_sha = sha256_file(base)
    excludes = read_excludes(a.exclude)

    r6 = os.path.join(staging, 'r6')
    if os.path.exists(r6):
        shutil.rmtree(r6)
    os.makedirs(os.path.join(r6, 'scripts'))
    os.makedirs(os.path.join(r6, 'cache'))
    os.makedirs(os.path.join(r6, 'logs'))
    shutil.copyfile(base, os.path.join(r6, 'cache', 'final.redscripts'))

    inputs, excluded = [], []

    # Codeware, composed from the repository like the Windows package.
    version = compose_mod.default_version()
    src_excl = sorted(e[len('Codeware-src/'):] for e in excludes if e.startswith('Codeware-src/'))
    bundles = compose_mod.compose(a.codeware_scripts, 'Codeware', version, src_excl)
    cw_dir = os.path.join(r6, 'scripts', 'Codeware')
    os.makedirs(cw_dir)
    for scope in sorted(bundles):
        rel = 'Codeware/%s.reds' % scope
        data = bundles[scope].encode('ascii', 'replace')
        if rel in excludes:
            excluded.append(rel)
            continue
        with open(os.path.join(cw_dir, scope + '.reds'), 'wb') as f:
            f.write(data)
        inputs.append({'path': rel, 'sha256': hashlib.sha256(data).hexdigest(),
                       'source': 'composed from %s (Codeware %s)' % (a.codeware_scripts, version)})

    # Other mods under r6/scripts, then the plugins' Scripts folders.
    mods_dir = os.path.join(game, 'r6', 'scripts')
    for name in sorted(os.listdir(mods_dir)) if os.path.isdir(mods_dir) else []:
        if name == 'Codeware' or not os.path.isdir(os.path.join(mods_dir, name)):
            continue
        copy_tree(os.path.join(mods_dir, name), os.path.join(r6, 'scripts', name), name, excludes, inputs, excluded,
                  'game r6/scripts/%s' % name)
    plug_dir = os.path.join(game, 'red4ext', 'plugins')
    overrides = {}
    for item in a.plugin_scripts:
        if '=' not in item:
            print('build-cache: --plugin-scripts wants NAME=DIR, got %r' % item, file=sys.stderr)
            return 2
        pname, pdir = item.split('=', 1)
        pdir = os.path.abspath(os.path.expanduser(pdir))
        if not os.path.isdir(pdir):
            print('build-cache: --plugin-scripts folder not found: %s' % pdir, file=sys.stderr)
            return 2
        overrides[pname] = pdir
    composed_dirs = []
    for item in a.compose_scripts:
        if '=' not in item:
            print('build-cache: --compose-scripts wants NAME=DIR[@VERSION], got %r' % item, file=sys.stderr)
            return 2
        pname, rest = item.split('=', 1)
        pdir, _, pver = rest.partition('@')
        pdir = os.path.abspath(os.path.expanduser(pdir))
        if not os.path.isdir(pdir):
            print('build-cache: --compose-scripts folder not found: %s' % pdir, file=sys.stderr)
            return 2
        out_dir = os.path.join(staging, 'composed', pname)
        if os.path.exists(out_dir):
            shutil.rmtree(out_dir)
        os.makedirs(out_dir)
        for scope, text in sorted(compose_mod.compose(pdir, pname, pver or '0.0.0', []).items()):
            with open(os.path.join(out_dir, scope + '.reds'), 'wb') as f:
                f.write(text.encode('ascii', 'replace'))
        overrides[pname] = out_dir
        composed_dirs.append(pname)
    names = set(os.listdir(plug_dir)) if os.path.isdir(plug_dir) else set()
    names |= set(overrides)
    for name in sorted(names):
        sdir = overrides.get(name) or os.path.join(plug_dir, name, 'Scripts')
        if name == 'Codeware' or not os.path.isdir(sdir):
            continue
        dst = os.path.join(r6, 'scripts', name)
        if os.path.exists(dst):
            print('build-cache: warning: %s exists both in r6/scripts and as a plugin; the plugin files are merged in' % name,
                  file=sys.stderr)
        label = ('composed from the sources of %s' % name) if name in composed_dirs else ('plugin scripts override %s' % sdir) if name in overrides else ('plugin red4ext/plugins/%s/Scripts' % name)
        copy_tree(sdir, dst, name, excludes, inputs, excluded, label)

    # The macOS self-test scripts (a scripted class with OnConstruct for the R19 test).
    if a.extra_scripts and os.path.isdir(a.extra_scripts):
        copy_tree(a.extra_scripts, os.path.join(r6, 'scripts', 'CodewareMacDiag'), 'CodewareMacDiag', excludes, inputs,
                  excluded, 'repo tools/diag-scripts')

    inputs_h = hashlib.sha256()
    for e in sorted(inputs, key=lambda e: e['path']):
        inputs_h.update((e['path'] + ' ' + e['sha256'] + '\n').encode())
    fingerprint = hashlib.sha256((inputs_h.hexdigest() + ' ' + base_sha + '\n').encode()).hexdigest()
    if a.dry_run:
        print('build-cache: %d input files, %d excluded, base cache %s' % (len(inputs), len(excluded) + len(src_excl), base_sha[:12]))
        print('FINGERPRINT=' + fingerprint)
        return 0

    # Compile through scc_nopopup.py.
    tmp_out = os.path.join(staging, 'final.redscripts.new')
    if os.path.exists(tmp_out):
        os.remove(tmp_out)
    proc = subprocess.run([sys.executable, SCC, r6, tmp_out], capture_output=True, text=True)

    # The exit code of scc_nopopup.py is not usable here: libscc_lib's scc_get_success returns false for a compile that
    # finished and saved its output (checked on the known-good gate5b set and on this tree), and the script turns that
    # into exit 1. The decision comes from the log and the output file instead: success means "Compilation complete",
    # "Output successfully saved", no [ERROR line, and a fresh output file.
    log = os.path.join(r6, 'logs', 'redscript_rCURRENT.log')
    log_text = open(log, errors='replace').read() if os.path.isfile(log) else ''
    log_errors = [ln.rstrip() for ln in log_text.splitlines() if '[ERROR' in ln or 'compilation has failed' in ln.lower()]
    ok = ('Compilation complete' in log_text and 'Output successfully saved' in log_text and not log_errors
          and os.path.isfile(tmp_out) and os.path.getsize(tmp_out) > 0)
    errors = (proc.stderr.strip() + '\n' + proc.stdout.strip()).strip() if not ok else ''
    if not ok:
        # Keep the compiler's full error blocks, not just the first lines.
        errors = '\n'.join(ln for ln in log_text.splitlines()) if log_text else errors
    os.makedirs(os.path.dirname(out_cache), exist_ok=True)
    with open(out_cache + '.errors.txt', 'w') as f:
        if not ok:
            f.write(errors + '\n')
    if ok:
        shutil.move(tmp_out, out_cache)
    elif os.path.exists(out_cache):
        os.remove(out_cache)

    manifest = {
        'game_dir': game,
        'staging': staging,
        'base_cache': {'path': base, 'sha256': base_sha, 'is_stock_cache': base_sha == STOCK_CACHE_SHA256},
        'compiler': SCC,
        'codeware_version': version,
        'inputs': sorted(inputs, key=lambda e: e['path']),
        'excluded': sorted(excluded) + ['Codeware-src/' + e for e in src_excl],
        'exclude_file': a.exclude if os.path.exists(a.exclude) else None,
        'result': {
            'ok': ok,
            'cache': out_cache if ok else None,
            'cache_sha256': sha256_file(out_cache) if ok else None,
            'cache_bytes': os.path.getsize(out_cache) if ok else None,
            'error_line_count': len(log_errors),
        },
    }
    h = hashlib.sha256()
    for e in manifest['inputs']:
        h.update((e['path'] + ' ' + e['sha256'] + '\n').encode())
    manifest['inputs_sha256'] = h.hexdigest()
    manifest['fingerprint'] = fingerprint
    with open(out_cache + '.manifest.json', 'w') as f:
        json.dump(manifest, f, indent=2)
        f.write('\n')

    print('build-cache: %d input files, %d excluded, base cache %s%s' % (
        len(inputs), len(excluded) + len(src_excl), base_sha[:12], '' if base_sha == STOCK_CACHE_SHA256 else ' (NOT the stock cache)'))
    if ok:
        print('build-cache: compiled %s sha256=%s (%d bytes)' % (out_cache, manifest['result']['cache_sha256'],
                                                                 manifest['result']['cache_bytes']))
    else:
        print('build-cache: COMPILE FAILED, %d error lines, see %s.errors.txt' % (len(log_errors), out_cache))
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
