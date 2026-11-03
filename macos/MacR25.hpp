#pragma once

// R25. Self-test of the CString copy semantics through the SDK (the CString_copy row is the copy assign, 0x2AACC). SELFTEST R25.
// Runs once at codeware_postLoadScripts, only when CODEWARE_MAC_DIAG=1. It uses only the SDK's own CString API.

namespace Mac
{
void R25SelfTest();
}
