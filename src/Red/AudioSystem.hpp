#pragma once

namespace Red
{
struct SoundBankEntry
{
    using AllocatorType = Memory::AudioSystemsAllocator;

    CName name;
    bool isResident;
    ResourcePath resourcePath;
};
}

namespace Red::SoundBankManager
{
using RegisteredBanks = Core::OffsetPtr<0x68, HashMap<CName, SharedPtr<SoundBankEntry>>>;
}

namespace Raw::SoundBankManager
{
constexpr auto ReadSoundBanksJson = Core::RawFunc<
    /* addr = */ Red::AddressLib::SoundBankManager_ReadSoundBanksJson,
    /* type = */ void (*)(void* aThis)>();
}
