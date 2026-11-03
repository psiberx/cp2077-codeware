# Codeware for macOS (Apple Silicon)

A port of [psiberx/cp2077-codeware](https://github.com/psiberx/cp2077-codeware) (1.20.5, upstream commit 613a1cb8, the same commit as 1.20.4) to the native Steam build of Cyberpunk 2077 for
Apple Silicon (game 2.3.1, arm64). The Windows build 20383525 is the reference for every address and layout. Port by codeman101 (skyman3215).
MIT, like upstream. Do not copy the Windows `Codeware.dll`.

This file describes the Mac layer: `macos/`, the `__APPLE__` branches in `src/` and `lib/`, and `tools/mac/`.
`macos/WINDOWS_CHECK.md` lists every shared file that differs from upstream, for review before a Windows build.
The Mac build file (`macos/CMakeLists.txt`) reads the version string from upstream's `xmake.lua`, which says 1.20.4 at the v1.20.5 tag, so the
Mac build reports 1.20.4 like upstream's own build of that tag. The build manifest records `git describe` to show which tag is merged.

## What works

Seen in menu boots of the release build (the `[selftest]` lines in `INGAME_TESTS.md` name the proof for each line):

| area | state |
|---|---|
| Plugin load, native class registration, the whole Codeware script type list (about 115 natives) | works; the script cache links with no `LINKERR` |
| Script validator layer and opcode handlers (the native types the Mac compiler spells differently) | works |
| Script services (`ScriptableService`, `OnLoad`, `OnInitialize`, `OnReload`, `OnBeforeGameSave`), service state files | works at the menu; the second-start restore and a save in a world are listed as in-game tests |
| `GameInstance` capture, `GetGameInstance` from script | works |
| Callback system: Resource/Load and PostLoad, Entity/* lifecycle, Component/Toggle, Vehicle/ToggleAuxLights, Session/*, Input/Key and Axis, InkWidget/Spawn | hooks installed and counted at the menu; the events that need a loaded world are in-game tests |
| Job runtime (`JobQueue`, groups, capture and join), no-wait dispatch | works (menu self-test) |
| `ResourcePathRegistry`, `ResourceTarget.Path`, localization merge (`ModLocalizationProvider`) | works |
| Entity, dynamic and static entity systems, tags, persistency, weather, community and open-world wrappers | rows and layouts checked, tests at the menu and in game |
| Ink UI: widget library spawns, external library injection, controllers, text input, key translation | works at the menu (Equipment-EX wardrobe and Lizzie's UI) |

## Requirements

- macOS 14 or newer, Apple Silicon, Xcode command line tools, CMake 3.21+, Homebrew `spdlog` and `fmt`.
- The game 2.3.1 (Steam, native Mac build) and RED4ext-macos with the Frida gadget. The Windows-only classes the Mac game lacks are left out
  of the script cache (`tools/build-cache.exclude`).
- The sibling checkout `../RED4ext.SDK-macos` on its `mac-full` branch (or `-DRED4EXT_SDK_DIR=<dir>`). Never build against an SDK without the
  Mac `SharedSpinLock` protocol: Codeware takes locks that the game owns.

## Build

From the parent folder of the three repos: `tools/build-all.sh` builds Codeware, TweakXL and ArchiveXL and collects the signed results with
sha256 sums. For this repository alone:

```sh
cmake -S macos -B macos/build -DRED4EXT_SDK_DIR=../RED4ext.SDK-macos
cmake --build macos/build -j
```

The post-build steps rewrite the install names to `@loader_path` (`macos/fix-install-names.sh`) and fail the build when the dylib needs a
symbol of the Codeware namespaces that it does not define (`macos/check-undefined.sh`).

## Script cache

The game links its scripts at start, so the Codeware scripts have to be compiled into a script cache together with the other script mods:
`tools/build-cache.py <game> <out>` builds it outside the game folder (it never calls `engine/tools/scc` directly, which opens a modal
alert on every failed compile, but `tools/scc_nopopup.py` in the parent folder). `--dry-run` prints a fingerprint of the inputs so a launcher can
rebuild only when something changed.

## Runtime hooks and the allowlist

RED4ext-macos installs a detour only on offsets listed in `RED4EXT_GUM_HOOK_OFFSETS`. For any other offset `Attach` reports success and hands
back the target itself as the original, which is a silent no-op. `macos/hook-offsets.txt` lists the offsets Codeware hooks; `tools/build-all.sh`
merges it with the lists of the other two plugins into `GUM_OFFSETS.txt`. The hooks are entry-only (the first instructions are relocated by
frida-gum); one hook per target is the rule, so Codeware and ArchiveXL chain on the four targets they share through
`codeware_mac_hook_chain_attach` and `archivexl_mac_hook_chain_attach`.

## Environment variables

| variable | effect |
|---|---|
| `CODEWARE_MAC_DIAG=1` | diagnostics and all self-tests (also switches on ArchiveXL's). Default: off, the log has only normal lines, errors and the trap reports. |
| `CODEWARE_MAC_NOHOOKS=<name,...>`, `CODEWARE_MAC_SYSTEMS=<list>`, `CODEWARE_MAC_SYSTEMS_OFF=<list>` | switch single callback hooks or game systems off for a session (bisecting a crash). |
| `CODEWARE_MAC_ONCONSTRUCT=0` | do not dispatch `OnConstruct` of scripted classes. |
| `CODEWARE_MAC_SAVE_JOBS=1` | dispatch the service state save through a job group; default is the inline call. |
| `CODEWARE_MAC_DUMP_REFLECTION=<file>` | write the game's reflection (classes, properties, offsets) to a file at start; used by `tools/mac/gen-mac-layout.py`. |
| `CODEWARE_R16A_CRASHTEST=<s>`, `CODEWARE_R16A_CRASHMODE=<mode>` | with `CODEWARE_MAC_DIAG=1` only: crash on purpose after `<s>` seconds, to test the crash report. |
| `CODEWARE_R13_SELFTEST_CB=1` | with `CODEWARE_MAC_DIAG=1` only: register the static callback self-test. |

Crash reports (`[crash]` lines with the top frames, then a clean exit) are always on.

## Mac ABI notes

- `this` is in x0; a result that is not trivially copyable (Handle, SharedPtr, CString, DynArray, JobHandle) comes back through x8 and the
  Windows `T& aOut` argument disappears. A `HookBefore` on such a function needs a Raw return type that clang also returns through x8
  (`Red::SretValue<N>` with a user-provided destructor, `src/Red/Common.hpp`, Apple only).
- The vtable has one extra leading slot: the Mac slot is the Windows slot plus 8 (`Core::RawVFunc` adds it; the third template argument marks a
  slot as verified). Overloaded virtuals are laid out in the opposite order from MSVC.
- Two-float results come back in `s0:s1`; 8 byte values (`CName`, `ResourcePath`, `TweakDBID`) travel in x0.
- The Mac compiler reuses the tail padding of non-POD bases, so 1,341 of the game's reflected members sit at other offsets than the SDK's
  Windows headers. `macos/MacLayoutGuard.cpp` (generated by `tools/mac/gen-mac-layout.py`) turns that into `static_assert`s for the classes the plugin
  sees. `tools/mac/check-sdk-layout.py --dump layout/reflection-<date>.tsv` does the same for every class the SDK declares (18,601 member offsets in
  5,024 classes at R25: 0 wrong, 0 negative padding arrays; 59 members stay unchecked because 23 headers do not compile for reasons unrelated to the
  layout). A header that only compiles alone is not enough: run it after any change of the SDK headers or of the generator.
- Locks the game owns (`SharedSpinLock`) follow the game's protocol on Apple: bit 7 is the writer, the low bits count readers.

## Test-only: key injection for the unattended runs

`macos/MacAutotest.mm` and `CodewareMacSelfTest.PostKey` hand a Space event to the game's own `GameView` inside the process, so that the owner's
`tools/autotest` runs can pass the start screen and the "press to continue" prompt of a load. It is not a Codeware feature and is left out of anything
user-facing: it does nothing unless the environment has `CP2077_AUTOTEST=1` (only `tools/autotest/run.sh` sets it), a default session or
`launch_modded.sh` never has it, and no default script cache declares the native. It runs on the main thread, never leaves the process (no
`CGEventPostToPid`, no macOS permission) and logs every key as an `[autotest]` line.
`CodewareMacSelfTest.DumpObject` (`macos/MacAutotestDump.cpp`, same gate) prints a game object through the RTTI as `[dump]` lines (class, properties,
handles, arrays; a weak handle is dereferenced only while its reference block still has a strong reference). It is read only. `DumpScriptable` is the same for scripted objects (components, puppets, controllers).
Known upstream behaviour, not changed: `Reflection.GetClassOf(ToVariant(null))` dereferences a null instance; a script has to check the handle first.

## Known gap: RED4ext's own exit code crashes (worked around in the plugin)

The installed RED4ext.dylib (NightCity Console build) crashes at the end of its own exit code on every normal quit: App::Destruct opens a DetourTransaction, does not commit it, and the destructor logs through an spdlog default logger that is already null (RED4ext.dylib+0xdb134; the same stack is in the 2026-10-03 crash reports, before any of our plugins). On Apple the last of our three plugins to unload leaves the process with _exit(0), only while the process is exiting (the Unload call must be inside libsystem_c's `exit()`, checked on the stack with backtrace and dladdr), after flushing its logs. Mac only (macos/MacExit.hpp). A plain Unload (reload, failed load, one plugin alone) never exits.
The plugin's `Main` (Unload) also leaves its application and extension objects alone (`g_app.release()`): they hold tokens and handles of the game, and
destroying them from RED4ext's atexit handler went through freed SDK relocation tables (the r27 quit crash, fixed in the SDK as well). Environment keys:
`CP2077_MAC_PLUGIN_AXL_STATE`, `CP2077_MAC_PLUGIN_CW_STATE`, `CP2077_MAC_PLUGIN_TXL_STATE` ("loaded" / "unloaded").

## Known gap: a script that drops the last reference to a resource token leaks it (Mac only)

`ResourceDepot.LoadResource` returns a `ResourceToken` wrapper. When the last script reference goes, `SharedPtr` destroys the token with `Memory::Delete`,
which frees through the SDK's `EngineAllocator`; Codeware's vault has no `PoolEngine` entry (ArchiveXL's has) and the SDK token destructor cannot release the
game's Unk38 pointer on Mac, so that path faulted (null+0x10 in `Allocator<PoolEngine>::Free`, found by the `questdump` run of `tools/autotest`). On Apple
`App::ResourceTokenWrapper` keeps one extra strong reference for the rest of the process, so a token (and its resource) loaded this way is never destroyed
by the plugin. The token the game keeps in its own bank is untouched. Windows is unchanged (`src/App/Depot/ResourceToken.hpp`, Apple branch).

## Files

- `macos/NOT_YET.md`: every address hash without a Mac address (66 traps), what each trap does, and the known stand-ins. Generated by
  `tools/mac/gen-not-yet.py`.
- `macos/ADDRESS_CHECK.md`: every address row, vtable slot, field offset and registered property checked against the Windows twin.
- `macos/INGAME_TESTS.md`: what only fires in game, with the log line that proves it.
- `macos/hook-offsets.txt`: the allowlist offsets of this plugin.
- `macos/MacTrapTable.inc`, `MacSdkRows.inc`, `MacHookStubs.inc`, `MacLayoutGuard.cpp`: generated or table files, see `tools/mac/`.
- `macos/MacR*.cpp`, `MacEngine.cpp` (`DIAG`/`SELFTEST` code): run only with `CODEWARE_MAC_DIAG=1`. The `R<n>` in the names is the order the
  checks were written in; the log lines keep those tags (`[selftest] R19 ...`) as test ids.
