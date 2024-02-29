#pragma once

namespace Raw::MorphTargetManager
{
constexpr auto ApplyMorphTarget = Core::RawFunc<
    /* addr = */ Red::AddressLib::MorphTargetManager_ApplyMorphTarget,
    /* type = */ void (*)(Red::IComponent* aManager, Red::CName aTarget, Red::CName aRegion, float aValue, bool a5)>();
}
