#pragma once

// R22. One hook per target, across plugins.
//
// RED4ext on macOS accepts one hook per target address: a second Attach on the same target from another plugin fails. Codeware and
// ArchiveXL both hook some of the same game functions (ResourcePath::Create, the ink widget library spawns, localization loads,
// entity and resource events). This is the hand-off:
//
//   * Every hook a plugin attaches goes to RED4ext through a forwarding stub (MacHookStubs.inc): a tail jump (adrp/ldr/br, registers
//     untouched, x16 is the scratch register) to the function pointer in the stub's slot. The slot holds the plugin's detour.
//   * A plugin that finds the target already hooked by another plugin does not call RED4ext. It asks that plugin through an exported C
//     function (<owner>_mac_hook_chain_attach). The owner puts the new detour in the slot and hands back the previous slot value as the
//     new plugin's "original": the new detour runs first and calls the previous detour, which calls its own trampoline into the game.
//   * The plugins find each other with dlsym (flat namespace: the exported names are unique per plugin).
//
// The hook semantics of Core::HookingAgent (before, after, wrap, the original) are unchanged: the chained detour has the target's
// signature, so it is called like an original function.

#include <cstddef>
#include <cstdint>

namespace Mac::HookChain
{
// Attaches a detour to a game address through RED4ext (hook is a callable that does the real Attach) or by chaining on a hook of another
// plugin. Returns true when the detour is in place; *aOriginal is the function to call for the original behaviour.
using AttachFn = bool (*)(uintptr_t aTarget, void* aDetour, void** aOriginal, void* aContext);

bool Attach(uintptr_t aTarget, void* aDetour, void** aOriginal, AttachFn aRealAttach, void* aContext);

// True when this plugin owns a stub for the target (it attached it through RED4ext).
bool Owns(uintptr_t aTarget);

// Number of chained attaches this plugin accepted from other plugins, and its stubs in use (diagnostics).
unsigned ChainedCount();
unsigned StubsInUse();
}

// R22. Shared plugin state. On Windows the plugins of this family share some objects (for example the ResourcePath registry, so the
// ResourcePath::Create hook is installed once) through two fields of the game's CRTTISystem that the macOS layout does not have.
// Here the plugins hand an instance to each other through exported functions: the first plugin that publishes a name keeps the
// instance, the others find it with Acquire (it asks every other loaded plugin). The size guards against two plugins that disagree on
// the layout of the shared type; on a mismatch Acquire answers null and the caller builds its own instance.
namespace Mac::Shared
{
void* Acquire(uint64_t aName, std::size_t aSize);
void Publish(uint64_t aName, std::size_t aSize, void* aInstance);
}
