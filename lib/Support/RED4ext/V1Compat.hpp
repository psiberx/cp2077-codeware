#pragma once

// The Windows RED4ext SDK and the current macOS SDK both have the v1 plugin API
// (RED4ext::v1::PluginHandle, RED4ext::v1::Sdk). This header used to alias those names
// onto the v0 types on macOS. The aliases are gone; the v1 headers are native.

#if defined(__APPLE__)

#include <RED4ext/Api/v1/Sdk.hpp>

#endif
