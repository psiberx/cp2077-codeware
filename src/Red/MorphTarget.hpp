#pragma once

#include "Red/Addresses.hpp"

namespace Raw::MorphTargetManager
{
constexpr auto ApplyMorphTarget = Core::RawFunc<
        /* addr = */ Red::Addresses::MorphTargetManager_ApplyMorphTarget,
        /* type = */ void (*)(Red::IComponent* aManager, Red::CName aTarget, Red::CName aRegion,
                              float aValue, bool a5)>();
}
