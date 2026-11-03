# Windows check for Codeware (mac-full against upstream 613a1cb8, the v1.20.4 and v1.20.5 tag)

This file lists the 105 shared source files outside `macos/`, `tools/mac/` and documentation that differ between upstream `613a1cb8` (R31 merge, 2026-10-09) and the mac-full tip at the time of writing, and says whether each change can affect the Windows build or Windows behaviour. It is a static comparison (Windows cannot be built here): each file was reduced to the text a Windows compiler sees (`__APPLE__` undefined, `_WIN32` defined) and compared with upstream, and every file with a remaining difference was read by hand. Result: 51 modified files are fully Apple-guarded, 1 is an ignore-rule change, 10 new files are unreachable from the Windows build or reduce to the old include, and 43 changes are unguarded, of which 36 are NO-OP and 7 are CHECK items that only need a Windows build to confirm.

## Summary table

| Measure | Files |
|---|---|
| Shared files changed outside macos/, tools/mac/ and documentation | 106 |
| Modified, Apple-guarded only (Windows-visible text identical to upstream) | 51 |
| Modified, non-code (ignore rules only) | 1 |
| Additions only (not compiled on Windows, or reducing to the old include) | 11 |
| Unguarded changes (modified files and compiled additions) | 43 |
| of which NO-OP (same behaviour on Windows) | 36 |
| of which CHECK, low risk (needs a Windows build to confirm) | 7 |
| of which CHECK, breaks or may break the Windows build | 0 |

## Shared files changed

NONE: every hunk is inside an `__APPLE__` branch, or a `_WIN32`/`#else` split whose Windows branch is the upstream text, or the file is new and unreachable from the Windows build. NO-OP: unguarded, but the same behaviour on Windows (reason given). CHECK: unguarded behaviour or compile change that Windows CI should build and review.

| file | kind | Windows impact | one-line reason |
|---|---|---|---|
| `.gitignore` | modified | NONE | Adds `macos/build/` and `!macos/CMakeLists.txt` ignore rules; no build input. |
| `lib/Core/Facades/Runtime.cpp`<br>`lib/Core/Facades/Runtime.hpp`<br>`lib/Core/Foundation/RuntimeProvider.cpp` | modified | NONE | Mac overloads (`IsASI(void*)`, `IsEXE(std::string_view)`, ctor taking `void*`) added in the `#else` of `_WIN32`; the Windows overloads are untouched. |
| `lib/Core/Foundation/RuntimeProvider.hpp`<br>`lib/Core/Runtime/ModuleImage.hpp`<br>`lib/Core/Runtime/OwnerMutex.hpp` | modified | NO-OP (risk: none) | `#include "Core/Win.hpp"` replaced by `Core/Platform.hpp`, which includes Win.hpp on Windows. |
| `lib/Core/Hooking/Detail.hpp` | modified | NONE | Apple-only early return in `HookResult` (a refused hook target logs and leaves the feature off instead of throwing); R26: Apple-only per-hook call counters (the include of `HookHits.hpp`, a call in `Attach`, a bump in `Handle`, a static counter member; every hunk is inside `#if defined(__APPLE__)`). |
| `lib/Core/Hooking/HookHits.hpp` | added | NONE | New (R26). The whole content is inside `#if defined(__APPLE__)`; only `Detail.hpp` includes it, and only on Apple. |
| `lib/Core/Logging/LoggingAgent.cpp` | modified | NONE | Apple-only guard so `LogFlush` works before a logging driver is set. |
| `lib/Core/Platform.hpp` | added | NONE | New. On Windows it only includes `Core/Win.hpp`, which is what the including headers did before; the `#else` includes macOS.hpp. |
| `lib/Core/Raw.hpp` | modified | CHECK (risk: low) | `RawVFunc` gets a defaulted `bool VerifiedOnMac` template parameter and an extra `{}` scope around the call, and the file includes Platform.hpp. Windows ignores the flag and keeps `offset = A`. |
| `lib/Core/Runtime/HostImage.cpp` | modified | NO-OP (risk: none) | The six getters (GetBase, GetPath, GetName, GetRootDir, GetFileVer, GetProductVer) moved below the platform `#if` so both platforms share them; bodies identical to upstream. |
| `lib/Core/Runtime/HostImage.hpp` | modified | NO-OP (risk: none) | Adds `#include "Core/Platform.hpp"` (Win.hpp on Windows). |
| `lib/Core/Runtime/ModuleImage.cpp` | modified | NONE | Mac implementation (dladdr) in the non-Windows branch. |
| `lib/Core/Runtime/OwnerMutex.cpp` | modified | NONE | Mac file lock in /tmp stands in for the named mutex, non-Windows branch. |
| `lib/Core/Stl.hpp` | modified | NONE | Mac std containers in `#else`; the TiltedPhoques and hopscotch aliases stay in the `_WIN32` branch with the same text. |
| `lib/Core/Win.hpp` | modified | NONE | Windows includes now sit inside `#if _WIN32` with the same text; the `#else` includes `Core/macOS.hpp`. |
| `lib/Core/macOS.hpp` | added | NONE | Mac platform helpers; reachable only from non-Windows branches (Platform.hpp, Win.hpp, HostImage.cpp). |
| `lib/Red/Engine/Framework.hpp` | modified | NONE | Apple-only declarations (Mac game-instance accessors). |
| `lib/Red/Specializations.hpp` | modified | NO-OP (risk: none) | `size_t` to `uint64_t` in the enum `std::hash` specialisation; the same type on Windows x64. R28: the `std::hash<TweakDBID>` hunk (hash only the name hash and length, like `operator==`) is inside `#if defined(__APPLE__)`; the Windows branch is the upstream line. |
| `lib/Red/TypeInfo/Definition.hpp` | modified | CHECK (risk: low) | Adds `Red::Detail::InstancePtr` / `ConstInstancePtr` aliases (`void*` / `const void*` on Windows) for the `IsEqual`, `Assign`, `ConstructCls`, `DestructCls` overrides, so their signatures equal upstream; all other changes are Apple-only. |
| `lib/Red/TypeInfo/Macros/Definition.hpp` | modified | NO-OP (risk: none) | Appends `X_RTTI_FORCE_REGISTRAR(...)` to the RTTI_* macros; it is defined empty off Apple, so expansions are unchanged. |
| `lib/Red/TypeInfo/Registrar.hpp` | modified | NO-OP (risk: none) | Three unused static inline helpers (`RunPending`, `PendingRegisterCount`, `PendingDescribeCount`) over existing members. |
| `lib/Red/TypeInfo/Resolving.hpp` | modified | NO-OP (risk: none) | `IsScopedEnumName` becomes a template on `T` (T only matters in the Apple branch); the `"enum RED4ext::"` prefix and the result are unchanged; loop index typed `size_t` instead of `auto`. |
| `lib/Support/MinHook/MinHookProvider.cpp`<br>`lib/Support/MinHook/MinHookProvider.hpp` | modified | NO-OP (risk: none) | One comment line added. |
| `lib/Support/RED4ext/RED4extProvider.hpp` | modified | NO-OP (risk: none) | Adds `#include "Support/RED4ext/V1Compat.hpp"`, whose content is Apple-only. |
| `lib/Support/RED4ext/V1Compat.hpp` | added | NONE | `RED4ext::v1` aliases for the Mac SDK; whole content under `#if defined(__APPLE__)`. |
| `lib/Support/RedLib/RedLibProvider.cpp` | modified | NONE | Apple-only lifecycle include and queue handling. |
| `lib/Support/macOS/Lifecycle.hpp` | added | NONE | Mac lifecycle event dispatcher; included only from Apple branches. |
| `src/App/Application.cpp` | modified | NO-OP (risk: none) | Common includes pulled above an Apple/Windows include split; the Windows constructor is unchanged and `Migration::CleanUp` now sits in `#if !defined(__APPLE__)`. |
| `src/App/Application.hpp` | modified | NONE | Apple-only constructor declaration. |
| `src/App/Callback/CallbackSystem.cpp` | modified | NO-OP (risk: none) | Adds `#include <cstdio>`. |
| `src/App/Callback/CallbackSystem.hpp` | modified | NO-OP (risk: none) | Adds inline `HasCallbacks()` over the existing `m_callbacksLock` and `m_callbacksByEvent`; unused on Windows. |
| `src/App/Callback/CallbackSystemHandler.hpp`<br>`src/App/Callback/Controllers/EntityAttachHook.hpp`<br>`src/App/Callback/Controllers/ResourcePostLoadHook.hpp`<br>`src/App/Callback/Targets/ResourceTarget.hpp` | modified | NONE | Apple-only hooks and counters (job-body hooks, handler counters, Mac targets). |
| `src/App/Callback/Controllers/ComponentToggleHook.hpp`<br>`src/App/Callback/Controllers/EntityAssembleHook.hpp`<br>`src/App/Callback/Controllers/EntityDetachHook.hpp`<br>`src/App/Callback/Controllers/EntityExtractHook.hpp`<br>`src/App/Callback/Controllers/EntityRequestComponentsHook.hpp`<br>`src/App/Callback/Controllers/EntityUninitializeHook.hpp`<br>`src/App/Callback/Controllers/PlayerSpawnedHook.hpp`<br>`src/App/Callback/Controllers/RawInputHook.hpp`<br>`src/App/Callback/Controllers/VehicleLightControlHook.hpp` | modified | NO-OP (risk: none) | Adds `#include "App/Callback/MacHooks.hpp"` and `MAC_HOOK_ENTER("...")` as the first statement of the handler (two in EntityUninitializeHook); the macro is empty off Apple. |
| `src/App/Callback/Controllers/MacResourceJob.hpp`<br>`src/App/Callback/MacHookStats.hpp` | added | NONE | Mac-only; whole content under `#if defined(__APPLE__)`, included only from Apple branches. |
| `src/App/Callback/Controllers/ResourceLoadHook.hpp` | modified | NO-OP (risk: none) | Same `MAC_HOOK_ENTER` addition, plus `if (Dispatch(...))` split into `const bool dispatched = ...; if (dispatched)`. |
| `src/App/Callback/MacHooks.hpp` | added | NO-OP (risk: none) | Defines `MAC_HOOK_ENTER` on Apple and an empty `MAC_HOOK_ENTER(aName)` otherwise; compiled on Windows through the hook controllers. |
| `src/App/Depot/ResourceToken.hpp` | modified | NONE | Apple-only destructor of `ResourceTokenWrapper` that keeps one extra strong reference (the SDK delete path faults on Mac, see the README known gap). Windows compiles the unchanged class. |
| `src/App/Depot/ResourceDepot.hpp`<br>`src/App/Engine/JobQueue.hpp` | modified | NONE | Apple-only branches (Mac `JobQueue::Dispatch` closure form, depot declarations). |
| `src/App/Entity/ComponentWrapper.cpp` | modified | NO-OP (risk: none) | One comment line added. |
| `src/App/Entity/PersistencyService.cpp` | modified | NONE | Apple-only hook counter. |
| `src/App/Entity/SkinnedMeshComponentEx.hpp` | modified | NO-OP (risk: none) | The `meshResource` offset 0x200 moves into `App::SkinnedMeshHandleOffset` (still 0x200 on Windows, 0x1F8 under Apple). |
| `src/App/Localization/LocalizationService.cpp` | modified | NONE | Apple-only self-test counters. |
| `src/App/Scripting/ScriptableServiceContainer.cpp`<br>`src/App/Scripting/ScriptableServiceContainer.hpp`<br>`src/App/Scripting/ScriptingService.hpp` | modified | NONE | Apple-only game-instance initialisation path and lifecycle stand-ins for the ScriptBundle::Destruct hook. |
| `src/App/Scripting/ScriptingService.cpp` | modified | NO-OP (risk: none) | One comment line added; the rest is Apple-only. |
| `src/App/Shared/ResourcePathRegistry.cpp`<br>`src/App/Shared/ResourcePathRegistry.hpp` | modified | NONE | Apple-only hook-sharing counters and chaining with ArchiveXL. |
| `src/App/UI/WidgetBuildingService.cpp` | modified | NO-OP (risk: none) | The `IsLegacyController` result is stored in a local `legacy` before the `if`; same logic. |
| `src/App/UI/WidgetInputService.cpp`<br>`src/App/UI/WidgetSpawningService.hpp`<br>`src/App/UI/inkSystem.hpp` | modified | NONE | Apple-only key translation, Mac-ABI spawn hook declarations and ink layer helpers. |
| `src/App/UI/WidgetSpawningService.cpp` | modified | NO-OP (risk: none) | `InjectDependency` reads the library list through `ExternalLibrariesOf()` (returns `&aLibrary.externalLibraries` off Apple) with a null check; the same list is used. R28: `OnSpawnExternalMac` and `OnAsyncSpawnExternalMac` (Apple only) split `Item:Controller` names, inject the controller and dispatch `InkWidget/Spawn`; on Windows the game's SpawnFromExternal reaches the hooked local spawn that does this. |
| `src/App/Utils/NodeRef.hpp`<br>`src/App/Utils/String.hpp` | modified | NONE | Apple-only Mac function signature and string helpers. |
| `src/App/World/DynamicEntitySystem.cpp` | modified | NO-OP (risk: none) | Entity ID and population lookups go through `GameSystemCalls.hpp`, whose Windows branch makes the same virtual calls as upstream; `GetTagged` keeps the upstream loop on Windows. R33: the Apple-only `CreateStub` call (token through x8) is inside `#if defined(__APPLE__)`; the Windows branch is the upstream call. R33: the stub hand-off at the world detach (`OnAfterWorldDetach`) is Apple-only too; Windows clears the states as upstream does. |
| `src/App/World/OpenWorldSystem.cpp`<br>`src/App/World/StaticEntitySystem.cpp` | modified | NO-OP (risk: none) | Include `Red/GameSystemCalls.hpp` and call its helpers; the Windows branch makes the same virtual calls as upstream. |
| `src/App/World/OpenWorldTracker.cpp` | modified | NONE | Apple-only hook counter. |
| `src/App/World/WorldStateSystem.cpp` | modified | NO-OP (risk: none) | Adds `#include <cstdio>`; the rest is Apple-only. |
| `src/Red/Addresses/Library.hpp` | modified | NONE | Mac-only address ids (job bodies) in an Apple branch. |
| `src/Red/CommunitySystem.hpp`<br>`src/Red/JournalManager.hpp`<br>`src/Red/MappinSystem.hpp`<br>`src/Red/Mesh.hpp`<br>`src/Red/QuestsSystem.hpp` | modified | CHECK (risk: low) | Virtual-slot bindings get `RawVFunc<..., /* verified = */ true>` as a third template argument (ignored on Windows), plus Apple-only slot notes and wrappers; QuestsSystem.hpp also braces `__nop()` in two NDEBUG blocks. Depends on the Raw.hpp change. |
| `src/Red/Entity.hpp`<br>`src/Red/EntityBuilder.hpp`<br>`src/Red/GameInstance.hpp` | modified | NONE | Apple-only Mac ABI variants (TweakDBID in x0, builder and queue form, ScriptGameInstance builder). |
| `src/Red/EntitySpawner.hpp` | modified | NONE | Apple-only handle clearing in a member destructor. |
| `src/Red/GameSystemCalls.hpp` | added | NO-OP (risk: none) | New helpers; the `#else` branch makes the same virtual calls (`GetNextTransientID(id)`, `GetNextPersistableID(id)`, `FindEntity(out, id)`) as the upstream call sites. |
| `src/Red/InkCore.hpp`<br>`src/Red/InkLibrary.hpp`<br>`src/Red/Localization.hpp`<br>`src/Red/NodeRef.hpp`<br>`src/Red/Physics.hpp`<br>`src/Red/ResourceBank.hpp`<br>`src/Red/ResourcePath.hpp`<br>`src/Red/RuntimeScene.hpp`<br>`src/Red/Scripting.hpp`<br>`src/Red/VisualController.hpp` | modified | NONE | Apple-only Mac ABI variants (result through x8, changed argument lists); the Windows declarations are unchanged. |
| `src/Red/Puppet.hpp` | modified | NONE | Apple-only record-id field offset (0x25C). |
| `src/Red/ScriptBundle.hpp` | modified | NONE | Apple-only addition. |
| `src/Red/Serialization.hpp` | modified | NONE | Apple-only Mac job-body declarations. |
| `src/Red/SharedStorage.hpp` | modified | NONE | Apple-only cross-plugin instance sharing. |
| `src/Red/WorkspotSystem.hpp` | modified | NONE | Apple-only lock and map offsets. |
| `tools/build-cache.exclude`<br>`tools/build-cache.py`<br>`tools/compose-redscripts.py`<br>`tools/diag-scripts/CodewareMacDiag.reds` | added | NONE | Mac build and diagnostic helpers; not referenced by xmake.lua or tools/dist/*.ps1 (Windows packaging reads scripts/). |

## Remaining items for Windows CI

No known Windows compile break or behaviour change is open. A Windows CI build (xmake) is still needed to confirm these low-risk items:

- `lib/Core/Raw.hpp` and the five bindings that pass the new third argument (`src/Red/CommunitySystem.hpp`, `JournalManager.hpp`, `MappinSystem.hpp`, `Mesh.hpp`, `QuestsSystem.hpp`). Risk: low. `RawVFunc` and its partial specialisations gain `bool VerifiedOnMac` after a parameter pack (deducible, so standard C++); Windows keeps `offset = A` and the old call body, so behaviour is identical. Only compiler acceptance is open.
- `lib/Red/TypeInfo/Definition.hpp`. Risk: low. The `IsEqual`, `Assign`, `ConstructCls` and `DestructCls` overrides now take `Detail::ConstInstancePtr` / `Detail::InstancePtr`, which are `const void*` / `void*` on Windows, i.e. the upstream types and the ones the pinned psiberx SDK (`6ea7425`) declares. The same file's other changes are Apple-only. Confirm it builds, since this header is the one that must stay equal to upstream on Windows.

Everything else that still differs on the Windows side is rated NO-OP (risk: none): empty `MAC_HOOK_ENTER` and `X_RTTI_FORCE_REGISTRAR` macros, extra includes, include order, unused inline helpers (`Registrar.hpp`, `CallbackSystem::HasCallbacks`), the `GameSystemCalls.hpp` helpers (same virtual calls as upstream), `Resolving.hpp` (`IsScopedEnumName` made a template with an unused `T` off Apple), and small refactors that keep the logic (`WidgetBuildingService.cpp`, `WidgetSpawningService.cpp`, `ResourceLoadHook.hpp`).
