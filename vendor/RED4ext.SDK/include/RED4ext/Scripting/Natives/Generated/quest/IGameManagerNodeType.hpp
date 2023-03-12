#pragma once

// clang-format off

// This file is generated from the Game's Reflection data

#include <cstdint>
#include <RED4ext/Common.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ISignalStoppingNodeType.hpp>

namespace RED4ext
{
namespace quest { 
struct IGameManagerNodeType : quest::ISignalStoppingNodeType
{
    static constexpr const char* NAME = "questIGameManagerNodeType";
    static constexpr const char* ALIAS = NAME;

};
RED4EXT_ASSERT_SIZE(IGameManagerNodeType, 0x38);
} // namespace quest
} // namespace RED4ext

// clang-format on