#pragma once

namespace Raw::Vehicle
{
// Game 2.5 (exe 3.0.88.46235): the vehicle GetRecordID native (0xEBFFB4, registered at 0x21BB54D)
// reads [this+0x658]; 2.31's (0xE59F88, registered at 0x1CDEA6D) read [this+0x638].
// vehicleBaseObject grew 2976 -> 3008 bytes. The puppet one is unchanged (0xC7FAC8 reads +0x260).
using RecordID = Core::OffsetPtr<0x658, Red::TweakDBID>;
}
