#pragma once

// R13. Diagnostics and self-tests for the Mac hooks. Everything in MacR13.cpp is
// DIAG and SELFTEST (CODEWARE_MAC_DIAG=1 only).

namespace Mac
{
// ArchiveXLScripts.cpp. True when the game already has a class named ArchiveXL.
bool ArchiveXLClassExists();

// MacR13.cpp. Called once from codeware_postLoadScripts, after the R12 self-tests.
// Logs the hook counters, runs the NodeRef and ArchiveXL self-tests (and the R13 callback-chain test only when
// CODEWARE_R13_SELFTEST_CB is set), and starts a detached thread that logs the counters again 50 s later.
void R13PostLoadScripts();

// MacR13.cpp. R14. Starts the script services (ScriptableServiceContainer::OnInitializeScripts) at the end of
// codeware_postLoadScripts and logs the R14 callback and handler counts.
void R14StartServices();

// MacCrashDiag.cpp. DIAG R14. Installs a handler that prints the fault and the top frames on a fatal
// signal. Safe to call more than once: Steam's crash handler replaces it, so Main, postLoadScripts and a
// short-lived thread call it again.
void InstallCrashDiag();

// MacCrashDiag.cpp. DIAG R80. Logs the node setups and the worldInstancedMeshNode lists of one loaded streaming sector (read through
// the kernel, so a bad pointer cannot fault). Called from the load job hook (MacResourceJob.hpp) for the sectors it watches.
void LogSectorNodes(void* aSector, unsigned long long aPathHash);

// MacScratchTail.cpp. R81. Hooks the deserialize job's decode (0x1219C30) so that a package decoded into the serializer's scratch
// buffer is followed by zeros instead of an earlier package's bytes (the R79 crash). ScratchTailsZeroed counts the decodes it padded.
bool InstallScratchTailHook();
unsigned long long ScratchTailsZeroed();

// MacInstancedMeshGuard.cpp. R82. Hooks the worldInstancedMeshNodeInstance attach (0x1B1F1C8) so that an instance whose mesh index
// is outside its node's mesh list (an old-format mod node) is not attached instead of reading past the list (the Ghost Town SIGBUS).
// NoteInstancedMeshSector logs, once per sector, a loaded streaming sector that holds such nodes (called from MacResourceJob.hpp).
bool InstallInstancedMeshGuard();
unsigned long long InstancedMeshInstancesSkipped();
void NoteInstancedMeshSector(void* aResource, unsigned long long aPathHash);

// MacGameInstanceHook.cpp. R14. Hooks the GetGameInstance native (0x1F42944) at plugin load. After the original
// runs, an empty result is rebuilt with the live game instance when one exists. Needs the resolver and the driver.
bool InstallGetGameInstanceHook();

// MacR16a.cpp. SELFTEST R16a. Called at the start of codeware_postLoadScripts, after PatchScriptOpCodes. Checks the
// SDK address rows from MacSdkRows.inc and the CClass::GetProperty lookup EntityTarget::Matches uses, and logs
// "[selftest] R16a GetProperty PASS|FAIL (checks=N failed=M)". Arms a test crash only when CODEWARE_R16A_CRASHTEST is set.
void R16aSelfTest();

// MacR16b.cpp. SELFTEST R16b. Called once from ScriptableServiceContainer::OnWorldAttached (first world attach,
// at the menu). Dumps the game systems' vtables against Codeware's, calls IsSavingLocked on Codeware's systems with the
// Mac signature, then calls the game's own save-lock collector (0x3314DDC). Logs "[selftest] R16b ...".
void R16bSelfTest();

// MacR13.cpp. SELFTEST R18 B1. Registers one counting static script callback (CodewareMacSelfTest.OnAnyEvent) for every
// event kind the CallbackSystem supports. Called at the end of codeware_postLoadScripts on the engine thread, after the R14
// callback counts are logged. R18LogEventCounts logs "[selftest] R18 callbacks@<when> <event>=<deliveries> ..." and checks the
// event kinds that must reach a callback at the menu.
void R18RegisterEventCallbacks();
void R18LogEventCounts(const char* aWhen);
uint64_t R18EventDeliveries(); // sum of all deliveries, to see whether anything changed

// MacR17.cpp. SELFTEST R17. Called at the start of codeware_postLoadScripts. Logs "[selftest] R17 ..." and
// "[selftest] R17 PASS|FAIL (checks=N failed=M)".
void R17SelfTest();

// MacR17.cpp. DIAG R17. Lists RTTI properties without a type after the script types register.
void R17AuditPropertyTypes(const char* aWhen);
}
