#pragma once

namespace Red
{
struct ResourceSerializer
{
    uint8_t unk00[0x230];                          // 00
    DynArray<Handle<ISerializable>> serializables; // 230
};
RED4EXT_ASSERT_OFFSET(ResourceSerializer, serializables, 0x230);

struct DataBufferProxyStream : BaseStream
{
    DataBufferProxyStream(Red::DataBuffer& aBuffer)
        : BaseStream(2)
        , buffer(aBuffer)
    {
    }

    void* ReadWrite(void* aBuffer, uint32_t aLength) override
    {
        if (aLength == 4)
        {
            *reinterpret_cast<uint32_t*>(aBuffer) = buffer.buffer.size;
        }
        else if (aLength == buffer.buffer.size)
        {
            std::memcpy(aBuffer, buffer.buffer.data, buffer.buffer.size);
        }

        return nullptr;
    }

    size_t GetPointerPosition() override
    {
        return 0;
    }

    size_t GetLength() override
    {
        return 0;
    }

    bool Seek(size_t aDistance) override
    {
        return false;
    }

    bool Flush() override
    {
        return false;
    }

    Red::DataBuffer& buffer;
};
}

namespace Raw::ResourceSerializer
{
constexpr auto OnDependenciesReady = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_OnDependenciesReady,
    /* type = */ void (*)(Red::ResourceSerializer* aSerializer)>();

constexpr auto OnResourceReady = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_OnResourceReady,
    /* type = */ void (*)(Red::ResourceSerializer* aSerializer)>();
}

namespace Raw::ObjectSerializer
{
constexpr auto WriteObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_WriteToBuffer,
    /* type = */ void* (*)(Red::DataBuffer& aBuffer,
                           Red::Handle<Red::ISerializable>& aObject,
                           int64_t a3,
                           uint32_t aFlags)>();

constexpr auto ReadObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_ReadFromStrean,
    /* type = */ void* (*)(Red::Handle<Red::ISerializable>& aObject,
                           Red::BaseStream& aStream,
                           Red::CClass* aObjectType)>();
}
