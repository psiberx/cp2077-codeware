#pragma once

namespace Raw::PhysicsTraceResult
{
// Game 2.5: not re-derived; physicsTraceResult is still 0x60 with the same RTTI fields.
using ResultID = Core::OffsetPtr<0x48, uint32_t>;

constexpr auto GetHitObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhysicsTraceResult_GetHitObject,
    /* type = */ Red::Handle<Red::ISerializable> (*)(uint32_t aResultID, uint32_t aIndex)>();
}
