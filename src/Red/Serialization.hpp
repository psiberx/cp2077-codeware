#pragma once

#include "Core/Facades/Hook.hpp"

namespace Red
{
struct ResourceSerializer
{
    uint8_t unk00[0x230];                          // 00
    DynArray<Handle<ISerializable>> serializables; // 230
};
RED4EXT_ASSERT_OFFSET(ResourceSerializer, serializables, 0x230);

struct ObjectSerializerParams
{
    uint32_t flags;           // 00
    ECookingPlatform cooking; // 04
    uint32_t sizeLimit;       // 08
    bool unk0C;               // 0C
    bool unk0D;               // 0D
    bool unk0E;               // 0E
    bool unk0F;               // 0F
};
RED4EXT_ASSERT_SIZE(ObjectSerializerParams, 0x10);
RED4EXT_ASSERT_OFFSET(ObjectSerializerParams, flags, 0x0);
RED4EXT_ASSERT_OFFSET(ObjectSerializerParams, sizeLimit, 0x8);

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
constexpr auto Prepare = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_Prepare,
    /* type = */ void* (*)(void* a1, Red::ObjectSerializerParams* aParams)>();

constexpr auto WriteObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_WriteToBuffer,
    /* type = */ void* (*)(Red::DataBuffer& aBuffer,
                           const Red::Handle<Red::ISerializable>& aObject,
                           uint64_t a3, uint32_t aSizeLimit)>();

constexpr auto ReadObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_ReadFromStrean,
    /* type = */ void* (*)(Red::Handle<Red::ISerializable>& aObject,
                           Red::BaseStream& aStream,
                           Red::CClass* aObjectType)>();
}

namespace Red
{
struct ObjectSerializer
{
    template<class T>
    inline static void SaveToFile(const Red::Handle<T>& aObject, const std::filesystem::path& aPath)
    {
        constexpr uint32_t MagicSizeLimit = 1337;

        Core::Hook::Before<Raw::ObjectSerializer::Prepare>(+[](void*, Red::ObjectSerializerParams* aParams) {
            if (aParams->sizeLimit == MagicSizeLimit)
            {
                aParams->sizeLimit = 0;
                aParams->flags = 0x10000000;
            }
        });

        Red::DataBuffer buffer;
        Raw::ObjectSerializer::WriteObject(buffer, aObject, 0, MagicSizeLimit);

        std::ofstream out(aPath, std::ios::binary);
        out.write(reinterpret_cast<char*>(&buffer.buffer.size), sizeof(buffer.buffer.size));
        out.write(reinterpret_cast<char*>(&buffer.buffer.alignment), sizeof(buffer.buffer.alignment));
        out.write(reinterpret_cast<char*>(buffer.buffer.data), buffer.buffer.size);
    }

    template<class T>
    inline static void ReadFromFile(Red::Handle<T>& aObject, const std::filesystem::path& aPath)
    {
        auto allocator = Red::RawBuffer::AllocatorType::Get();
        Red::DataBuffer buffer;

        std::ifstream in(aPath, std::ios::binary);
        in.read(reinterpret_cast<char*>(&buffer.buffer.size), sizeof(buffer.buffer.size));
        in.read(reinterpret_cast<char*>(&buffer.buffer.alignment), sizeof(buffer.buffer.alignment));

        buffer.buffer.data = allocator->AllocAligned(buffer.buffer.size, buffer.buffer.alignment).memory;

        in.read(reinterpret_cast<char*>(buffer.buffer.data), buffer.buffer.size);

        Red::DataBufferProxyStream stream(buffer);
        Raw::ObjectSerializer::ReadObject(aObject, stream, Red::GetClass<T>());

        allocator->Free(buffer.buffer.data);
    }
};
}
