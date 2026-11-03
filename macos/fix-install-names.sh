#!/bin/bash
# R14. Point Codeware.dylib at the copies of spdlog and fmt that sit next to it in the plugin folder
# (red4ext/plugins/Codeware/libspdlog.1.17.dylib, libfmt.12.dylib), the way TweakXL.dylib does.
# The build links the Homebrew copies by absolute path. This rewrites each dependency whose path contains
# libspdlog or libfmt to @loader_path/<file name>, then re-signs (ad hoc), because install_name_tool
# invalidates the signature. Usage: fix-install-names.sh <path to Codeware.dylib>
set -eu
DYLIB="$1"
for lib in libspdlog libfmt; do
  old=$(otool -L "$DYLIB" | awk -v pat="$lib" 'NR > 1 && index($1, pat) { print $1; exit }')
  if [[ -z "$old" ]]; then
    echo "fix-install-names: no $lib dependency found"
    continue
  fi
  case "$old" in
    @loader_path/*) echo "fix-install-names: $lib already $old" ;;
    *)
      new="@loader_path/$(basename "$old")"
      install_name_tool -change "$old" "$new" "$DYLIB"
      echo "fix-install-names: $old -> $new"
      ;;
  esac
done
codesign -f -s - "$DYLIB"
