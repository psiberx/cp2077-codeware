#pragma once

// R17 Part A. Diagnostics and self-tests on macOS run only when the environment has CODEWARE_MAC_DIAG=1.
// Crash reporting (MacCrashDiag) is not part of this: it is always on.
//
//   Mac::DiagEnabled()   true when CODEWARE_MAC_DIAG is "1". Read once.
//   MAC_DIAG(...)        std::fprintf(stderr, ...) that prints only when diagnostics are enabled.

#include <cstdio>

namespace Mac
{
bool DiagEnabled();
}

#define MAC_DIAG(...)                        \
    do                                       \
    {                                        \
        if (::Mac::DiagEnabled())            \
        {                                    \
            std::fprintf(stderr, __VA_ARGS__); \
        }                                    \
    } while (0)

// Prints always when `ok` is false (an error), and when diagnostics are enabled otherwise. Used for "hook installed / FAILED" lines.
#define MAC_DIAG_UNLESS(ok, ...)                                    \
    do                                                              \
    {                                                               \
        if (!(ok) || ::Mac::DiagEnabled())                          \
        {                                                           \
            std::fprintf(stderr, __VA_ARGS__);                      \
        }                                                           \
    } while (0)
