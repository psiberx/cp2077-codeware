#pragma once

// R15. Script validator layer and opcode handlers for the Mac port. Everything is in MacScriptValidator.cpp.
// The logic is a port of src/App/Scripting/ScriptingService.cpp (OnValidateScripts, OnValidateProperty,
// OnValidateScriptType, OnValidateTypeName, ScriptOpCodeNew, ScriptOpCodeCast). The Windows file is unchanged.

namespace Mac
{
// Hooks ScriptValidator::Validate (0x21FBF90) and ScriptValidator::ValidateProperty (0x21FCFB8). Needs the
// resolver and the driver. Both offsets must be on GUM_OFFSETS or RED4ext treats the hooks as no-ops.
bool InstallScriptValidatorHooks();

// Reads entries 48 (New) and 90 (Cast) of the opcode handler table (RVA 0x908B798) and logs them as RVAs.
// aStage "load": writes our handlers only when both entries are already set. Any other stage ("postLoadScripts"):
// writes them when they are not ours yet. Logs "[cw] R15 opcodes New 0x... -> ours, Cast 0x... -> ours".
void PatchScriptOpCodes(const char* aStage);

// R17. Names the property that ScriptValidator::ValidateProperty was last asked about ("Class.prop script=... native=..."),
// for the crash report. Empty when the validator has not run. Safe to call from the crash handler (best effort).
void DescribeLastValidatedProperty(char* aOut, unsigned long aSize);
}
