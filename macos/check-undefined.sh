#!/bin/bash
# R17 B3. The dylib links with -undefined dynamic_lookup (the game's own symbols resolve at load time), which also hides
# a Codeware function that was declared but never compiled in: the first call would crash. This lists every undefined
# symbol in Codeware's own namespaces and fails the build when there is one.
# Usage: check-undefined.sh <path to Codeware.dylib>
set -eu
DYLIB="$1"
ALLOW="$(dirname "$0")/undefined-allowed.txt"
BAD=$(nm -u -j "$DYLIB" | c++filt | grep -E '^(App|Core|Red|Support|Mac|Raw|RED4ext)::' || true)
if [[ -f "$ALLOW" && -n "$BAD" ]]; then
  BAD=$(echo "$BAD" | grep -vxFf <(grep -v '^#' "$ALLOW") || true)
fi
if [[ -n "$BAD" ]]; then
  echo "check-undefined: FAILED. These Codeware symbols are declared but not compiled into the dylib:" >&2
  echo "$BAD" >&2
  exit 1
fi
echo "check-undefined: ok (no undefined symbols in the Codeware namespaces)"
