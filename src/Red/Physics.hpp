#pragma once

namespace Raw::PhysicsTraceResult
{
using ResultID = Core::OffsetPtr<0x48, uint32_t>;

constexpr auto GetHitObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhysicsTraceResult_GetHitObject,
    /* type = */ Red::Handle<Red::ISerializable> (*)(uint32_t aResultID, uint32_t aIndex)>();
}
