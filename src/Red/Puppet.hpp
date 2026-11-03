#pragma once

namespace Raw::Puppet
{
#if defined(__APPLE__)
// R18. The Mac setter 0x378A7D0 (twin of Windows 0x1034238, which stores the id at +0x260) stores it at +0x25C. The field is
// not 8 byte aligned on Mac, so it is read and written with memcpy. Ref returns the value, not a reference.
struct RecordID
{
    static constexpr uintptr_t offset = 0x25C;

    static Red::TweakDBID Ref(const void* aBase)
    {
        Red::TweakDBID id{};
        std::memcpy(&id, reinterpret_cast<const uint8_t*>(aBase) + offset, sizeof(id));
        return id;
    }

    static void Set(void* aBase, Red::TweakDBID aId)
    {
        std::memcpy(reinterpret_cast<uint8_t*>(aBase) + offset, &aId, sizeof(aId));
    }
};
#else
using RecordID = Core::OffsetPtr<0x260, Red::TweakDBID>;
#endif
}
