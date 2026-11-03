#pragma once

namespace Raw::GameTagSystem
{
// Game 2.5: GameTagSystem.GetAnyMatchingEntity helper 0x2A23F9C `lea rbx,[rcx+0x48]` (0x2A23FAC).
using TagSystem = Core::OffsetPtr<0x48, Red::redTagSystem>;
}

namespace Raw::TagSystem
{
constexpr auto AssignTag = Core::RawFunc<
    /* addr = */ Red::AddressLib::TagSystem_AssignTag,
    /* type = */ void (*)(Red::redTagSystem* aSystem, Red::EntityID aEntityID, Red::CName aTag)>();

constexpr auto UnassignTag = Core::RawFunc<
    /* addr = */ Red::AddressLib::TagSystem_UnassignTag,
    /* type = */ void (*)(Red::redTagSystem* aSystem, Red::EntityID aEntityID, Red::CName aTag)>();
}
