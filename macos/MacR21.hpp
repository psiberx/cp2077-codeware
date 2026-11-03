#pragma once

// R21. Self-tests for the world, quest and entity rows (batch B5) and the layout guard. SELFTEST R21.
// Everything here runs on the engine thread that attaches the world (the thread the systems run on in production) and only calls
// functions Codeware calls itself; what changes game state (a tag assign) is undone at once.

#include <cstdint>

namespace RED4ext::world
{
struct RuntimeScene;
}
namespace Mac
{
void R21Check(bool aOk, const char* aWhat);
void R21Summary(const char* aWhen);

// Called at the world attach (ScriptableServiceContainer::OnWorldAttached, next to RuntimeSceneSelfTest): the weather getters, the
// community update.
void R21WorldAttachTests(RED4ext::world::RuntimeScene* aScene);

// Called by DynamicEntitySystem::OnWorldAttached when its tag system pointer exists: AssignTag and UnassignTag with a test entity.
void R21TagRoundTrip(void* aTagSystem);

// Called from StaticEntitySystem::OnRegisterUpdates (before and after the registration) and again from the t+50s thread: the entry
// counts of the update registrar's 14 groups and the raw words of the last entry of group 0 (diagnostics only).
void R21DumpRegistrar(void* aRegistrar, const char* aWhen);

// Entry count of the registrar's group 0 (FrameBegin), and the checks of the entry StaticEntitySystem::OnRegisterUpdates appended
// (called with the count read before the registration).
uint32_t R21RegistrarGroup0Count(void* aRegistrar);
void R21CheckRegistration(void* aRegistrar, uint32_t aCountBefore, const char* aName, void* aSystem);

// Called from the t+50s thread: the counters of the R21 hooks and callbacks.
void R21CheckAtT50();
}
