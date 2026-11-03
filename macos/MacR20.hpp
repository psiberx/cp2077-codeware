#pragma once

// R20. Self-tests for batch B4 (UI: ink widgets, layers, library spawns, controllers, character input). SELFTEST R20.
// The UI hooks run on the game's UI thread. The tests are one-shot, read-only checks made from inside the production hook (the
// same thread and the same data the service uses) and counters read at t+50s. Nothing here calls into the engine from another
// thread.

namespace Mac
{
// Tally of the R20 checks; "[selftest] R20 PASS|FAIL@<when> (checks=N failed=M)".
void R20Check(bool aOk, const char* aWhat);
void R20Summary(const char* aWhen);

// True for the first call only, per name (the one-shot checks inside the hooks use it).
bool R20Once(const char* aName);

// Called at the end of codeware_postLoadScripts, on the engine thread (no UI thread work here): the key translation check.
void R20PostLoadScripts();

// Called from the t+50s thread: reads the counters. Never calls into the engine.
void R20CheckAtT50();
}
