#pragma once

namespace Red
{
struct Serializer
{
    uint8_t unk00[0x230];                          // 00
    DynArray<Handle<ISerializable>> serializables; // 230
};
RED4EXT_ASSERT_OFFSET(Serializer, serializables, 0x230);
}

namespace Raw::Serializer
{
constexpr auto OnDependenciesReady = Core::RawFunc<
    /* addr = */ Red::AddressLib::Serializer_OnDependenciesReady,
    /* type = */ void (*)(Red::Serializer* aSerializer)>();

constexpr auto OnResourceReady = Core::RawFunc<
    /* addr = */ Red::AddressLib::Serializer_OnResourceReady,
    /* type = */ void (*)(Red::Serializer* aSerializer)>();
}
