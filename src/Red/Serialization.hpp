#pragma once

#include "Core/Facades/Hook.hpp"

namespace Red
{
struct ResourceSerializer
{
    uint8_t unk00[0x1D0];                          // 00
    uint8_t unk1D0[0x230 - 0x1D0];                 // 1D0
    DynArray<Handle<ISerializable>> serializables; // 230
};
// Game 2.5: ResourceSerializer_OnResourceReady 0x4B6C40 `lea rdi,[rcx+0x230]`, `lea r8,[rbx+0x1d0]`;
// OnDependenciesReady 0x2062660 `[rbx+0x1d0]`, `[rbx+0x23c]`, `[rbx+0x230]`.
RED4EXT_ASSERT_OFFSET(ResourceSerializer, unk1D0, 0x1D0);
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
constexpr auto SchedulePostLoadJobs = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_SchedulePostLoadJobs,
    /* type = */ void (*)(uint64_t a1, uint8_t a2, uint64_t a3, uint64_t a4, Red::ResourceSerializer** aCaptures)>();

constexpr auto ScheduleFinalizeJobs = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_ScheduleFinalizeJobs,
    /* type = */ void (*)(uint64_t a1, uint8_t a2, uint64_t a3, uint64_t a4, Red::ResourceSerializer** aCaptures)>();

#if defined(__APPLE__)
// R13. Mac job bodies. captures[0] is the ResourceSerializer*. Hooked at entry only.
// 0x2257548 runs when deserialization is done and post-load has not started.
constexpr auto MacLoadJob = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_MacLoadJob,
    /* type = */ void (*)(Red::ResourceSerializer** aCaptures, void* aJob)>();

// 0x2257830 runs when post-load is done and the requester has not received the list yet.
constexpr auto MacPostLoadJob = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_MacPostLoadJob,
    /* type = */ void (*)(Red::ResourceSerializer** aCaptures, void* aJob)>();
#endif

constexpr auto ExecutePostLoad = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_ExecutePostLoad,
    /* type = */ bool (*)(uint64_t a1, uint64_t a2, Red::JobQueue& aJobQueue)>();

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

#if defined(__APPLE__)
// Mac ABI (R19). The result comes back through x8 and the Windows out argument is gone, so every other argument moves up one
// register: WriteToBuffer takes (Handle*, flags, sizeLimit) and returns the DataBuffer by value, ReadFromStrean takes
// (stream, class) and returns the Handle by value. The Windows function ignores its third argument and builds the params with
// flags = -1; the Mac one takes the flags (both game callers pass -1).
constexpr auto WriteObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_WriteToBuffer,
    /* type = */ Red::DataBuffer (*)(const Red::Handle<Red::ISerializable>* aObject, uint32_t aFlags,
                                     uint32_t aSizeLimit)>();

constexpr auto ReadObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_ReadFromStrean,
    /* type = */ Red::Handle<Red::ISerializable> (*)(Red::BaseStream* aStream, Red::CClass* aObjectType)>();
#else
constexpr auto WriteObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_WriteToBuffer,
    /* type = */ Red::DataBuffer (*)(const Red::Handle<Red::ISerializable>& aObject,
                                     uint64_t a3, uint32_t aSizeLimit)>();

constexpr auto ReadObject = Core::RawFunc<
    /* addr = */ Red::AddressLib::ObjectSerializer_ReadFromStrean,
    /* type = */ void* (*)(Red::Handle<Red::ISerializable>& aObject,
                           Red::BaseStream& aStream,
                           Red::CClass* aObjectType)>();
#endif
}

namespace Red
{
struct ObjectSerializer
{
#if defined(__APPLE__)
    static constexpr uint32_t MagicSizeLimit = 1337;

    // R19. The Prepare hook (Mac 0x2161438) is installed at plugin load (ScriptingService::OnBootstrap), not at the first save, so
    // no thread is patched while it runs. SaveToFile calls it again; the second Before only replaces the identical callback.
    inline static bool InstallPrepareHook()
    {
        return static_cast<bool>(Core::Hook::Before<Raw::ObjectSerializer::Prepare>(+[](void*, Red::ObjectSerializerParams* aParams) {
            if (aParams->sizeLimit == MagicSizeLimit)
            {
                aParams->sizeLimit = 0;
                aParams->flags = 0x10000000;
            }
        }));
    }
#endif

    template<class T>
    inline static void SaveToFile(const Red::Handle<T>& aObject, const std::filesystem::path& aPath)
    {
#if defined(__APPLE__)
        InstallPrepareHook();
#else
        constexpr uint32_t MagicSizeLimit = 1337;

        Core::Hook::Before<Raw::ObjectSerializer::Prepare>(+[](void*, Red::ObjectSerializerParams* aParams) {
            if (aParams->sizeLimit == MagicSizeLimit)
            {
                aParams->sizeLimit = 0;
                aParams->flags = 0x10000000;
            }
        });
#endif

#if defined(__APPLE__)
        const Red::Handle<Red::ISerializable>& object = aObject;
        Red::DataBuffer buffer = Raw::ObjectSerializer::WriteObject(&object, 0xFFFFFFFFu, MagicSizeLimit);
#else
        auto buffer = Raw::ObjectSerializer::WriteObject(aObject, 0, MagicSizeLimit);
#endif

        std::ofstream out(aPath, std::ios::binary);
#if defined(__APPLE__)
        if (!out)
        {
            throw std::runtime_error("cannot open the file for writing");
        }
#endif
        out.write(reinterpret_cast<char*>(&buffer.buffer.size), sizeof(buffer.buffer.size));
        out.write(reinterpret_cast<char*>(&buffer.buffer.alignment), sizeof(buffer.buffer.alignment));
        out.write(reinterpret_cast<char*>(buffer.buffer.data), buffer.buffer.size);
    }

    template<class T>
    inline static void ReadFromFile(Red::Handle<T>& aObject, const std::filesystem::path& aPath)
    {
#if defined(__APPLE__)
        // The bytes live in plugin memory and the DataBuffer does not own them (no allocator is recorded), so the SDK's pool
        // allocators are not involved and nothing is freed twice.
        std::ifstream in(aPath, std::ios::binary);
        uint32_t size = 0;
        uint32_t alignment = 8;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        in.read(reinterpret_cast<char*>(&alignment), sizeof(alignment));

        std::vector<uint8_t> bytes(size);
        in.read(reinterpret_cast<char*>(bytes.data()), size);

        Red::DataBuffer buffer;
        buffer.buffer.data = bytes.data();
        buffer.buffer.size = size;
        buffer.buffer.alignment = alignment;

        Red::DataBufferProxyStream stream(buffer);
        auto object = Raw::ObjectSerializer::ReadObject(&stream, Red::GetClass<T>());
        aObject = Red::Cast<T>(object);

        buffer.buffer.data = nullptr; // not ours to free
#else
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
#endif
    }
};
}
