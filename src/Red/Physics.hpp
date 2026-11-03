#pragma once

namespace Raw::PhysicsTraceResult
{
// Game 2.5: not re-derived; physicsTraceResult is still 0x60 with the same RTTI fields.
using ResultID = Core::OffsetPtr<0x48, uint32_t>;

// Mac ABI (R21): the strong Handle comes back through x8 (resultID in w0, index in w1). Not the weak variant 0x409274C.
constexpr auto GetHitObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhysicsTraceResult_GetHitObject,
    /* type = */ Red::Handle<Red::ISerializable> (*)(uint32_t aResultID, uint32_t aIndex)>();
}
