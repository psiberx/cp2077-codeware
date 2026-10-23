#pragma once

namespace Raw::WardrobeSystem
{
// Game 2.5: 15 gameWardrobeSystem virtuals touch 0x48/0xF4 exactly as on 2.31 (0x35CE0E `lea rcx,[rbx+0x48]`,
// 0x35CE25 `lea rdx,[rbx+0xf4]`).
using ItemStore = Core::OffsetPtr<0x48, Red::HashMap<Red::CName, Red::ItemID>>;
using ItemStoreMutex = Core::OffsetPtr<0xF4, Red::SharedSpinLock>;
}
