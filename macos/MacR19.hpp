#pragma once

// R19. Self-tests for batches B2 (scripting) and B3 (depot, resources, localization). SELFTEST R19.
// They only read state or call the code paths Codeware itself runs in production, from the thread it runs them on.

namespace Mac
{
// Tally of the R19 checks; "[selftest] R19 PASS|FAIL@<when> (checks=N failed=M)".
void R19Check(bool aOk, const char* aWhat);
void R19Summary(const char* aWhen);

// Called at the end of codeware_postLoadScripts, on the engine thread that runs it (the one that registers callbacks and
// builds script handles in production). Runs the tests whose answer is known at once and starts the ones that are checked
// at t+50s.
void R19PostLoadScripts();

// CODEWARE_MAC_ONCONSTRUCT: unset or 1 = the OnConstruct dispatch is on (the default) and the self-test asserts it, 0 = off.
int R19OnConstructMode();

// Called by LocalizationService::OnLoadTexts for every LoadTexts call: the number of entries in the returned onscreens
// resource, how many of the first 64 have a text, and whether the path resolved to a language. Counters only.
void R19NoteLocalization(uint32_t aEntries, uint32_t aWithText, bool aLanguageKnown);

// Called from the t+50s thread: reads the results of the tests started by R19PostLoadScripts and the hook counters. Never
// calls into the engine.
void R19CheckAtT50();
}
