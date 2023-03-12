#pragma once

// clang-format off

// This file is generated from the Game's Reflection data

#include <cstdint>
#include <RED4ext/Common.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/VendorWare_Record.hpp>

namespace RED4ext
{
namespace game::data { 
struct VendorItem_Record : game::data::VendorWare_Record
{
    static constexpr const char* NAME = "gamedataVendorItem_Record";
    static constexpr const char* ALIAS = "VendorItem_Record";

    uint8_t unk58[0x60 - 0x58]; // 58
};
RED4EXT_ASSERT_SIZE(VendorItem_Record, 0x60);
} // namespace game::data
using VendorItem_Record = game::data::VendorItem_Record;
} // namespace RED4ext

// clang-format on