#pragma once

#if defined(_WIN32) || defined(_WIN64)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <wil/stl.h>
#include <wil/win32_helpers.h>

#else
// macOS: the platform header stands in for the Windows-only ones.
#include "Core/macOS.hpp"
#endif
