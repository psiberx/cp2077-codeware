#pragma once

// R17 Part B1. Fail-safe for address hashes that have no Mac address yet.
//
// Before: an unmapped hash resolved to 0 and the first call jumped to null (the Phase 6 crashes). Now every hash in
// the generated table (macos/MacTrapTable.inc: the Codeware address library and the RED4ext SDK hashes) has a
// compile-time trap stub, one template instantiation per hash. On its first call a trap logs
//   [cw] not on Mac yet: <name> (hash <n>) called from <image>+0x<off>
// and returns zero in x0 and x1. A data hash (RawPtr, UniversalRelocPtr) gets a zeroed buffer instead of code, so a
// read through it yields null.
//
// Limits (also in macos/NOT_YET.md):
//   * A function that returns a struct by value through x8 (CString, Handle, DynArray, anything with a destructor or
//     larger than 16 bytes) is not filled in by the generic trap. NOT_YET.md lists the unmapped ones.
//   * A function that returns a float or double gets whatever is in s0/d0.

#include <cstdint>

namespace Mac
{
// Address of the trap for a hash (code for a function, a zeroed buffer for data), or 0 when the hash is not in the table.
uintptr_t TrapFor(uint32_t aHash);

// True for the address of any trap stub or trap data buffer. The hooking driver refuses these as hook targets.
bool IsTrapAddress(uintptr_t aAddress);

// Name from the table, or nullptr.
const char* TrapName(uint32_t aHash);

// Number of hashes in the table and how many traps have fired so far.
unsigned TrapTableSize();
unsigned TrapHitCount();
}

// Used by the generated SDK relocation overlay (CMake injects the call). Returns the trap for an unmapped SDK hash.
extern "C" uintptr_t codeware_mac_trap_for_hash(uint32_t aHash);
