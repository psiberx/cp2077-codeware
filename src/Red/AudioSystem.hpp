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
// Game 2.5: SoundBankManager_ReadSoundBanksJson 0x953FB4 `mov r15,rcx` ... `lea rcx,[r15+0x68]` (0x954181).
using RegisteredBanks = Core::OffsetPtr<0x68, HashMap<CName, SharedPtr<SoundBankEntry>>>;
}

namespace Raw::SoundBankManager
{
constexpr auto ReadSoundBanksJson = Core::RawFunc<
    /* addr = */ Red::AddressLib::SoundBankManager_ReadSoundBanksJson,
    /* type = */ bool (*)(void* aThis)>();
}
