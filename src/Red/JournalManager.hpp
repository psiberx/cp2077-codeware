#pragma once

namespace Red
{
using JournalEntryHash = uint32_t;
}

namespace Raw::JournalManager
{
// Mac (R21, every slot checked against the game by body and call site): GetEntries 0x218, GetEntryState 0x2B8 and GetEntryTimestamp
// 0x2D0 are Windows + 8. The Itanium ABI keeps overloads in declaration order and MSVC reverses them, so GetEntryByHash (Mac 0x220) and
// the Handle overload of ChangeEntryState (Mac 0x268) sit at the same offset as on Windows: their address argument below is the
// Windows offset minus 8, which is what RawVFunc adds back. GetEntryByHash returns the Handle through x8 on Mac and has no out
// argument, so it gets a wrapper with the Windows call shape.
// Game 2.5: gameJournalManager slots 0x210/0x220/0x268/0x2B0/0x2C8 have the same code as on 2.31.
constexpr auto GetEntries = Core::RawVFunc<
    /* addr = */ 0x210,
    /* type = */ void* (Red::gameIJournalManager::*)(const Red::gameJournalRequestContext& aRequest,
                                                     Red::DynArray<Red::WeakHandle<Red::gameJournalEntry>>& aOut),
    /* verified = */ true>();

#if defined(__APPLE__)
constexpr auto GetEntryByHashNative = Core::RawVFunc<
    /* addr = */ 0x218,
    /* type = */ Red::Handle<Red::gameJournalEntry> (Red::gameIJournalManager::*)(Red::JournalEntryHash aEntryHash),
    /* verified = */ true>();

struct GetEntryByHashFn
{
    void* operator()(Red::gameIJournalManager* aManager, Red::Handle<Red::gameJournalEntry>& aOut,
                     Red::JournalEntryHash aEntryHash) const
    {
        aOut = GetEntryByHashNative(aManager, aEntryHash);
        return nullptr;
    }
};
inline constexpr GetEntryByHashFn GetEntryByHash{};

constexpr auto ChangeEntryState = Core::RawVFunc<
    /* addr = */ 0x260,
#else
constexpr auto GetEntryByHash = Core::RawVFunc<
    /* addr = */ 0x220,
    /* type = */ void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aOut,
                                                     Red::JournalEntryHash aEntryHash)>();

constexpr auto ChangeEntryState = Core::RawVFunc<
    /* addr = */ 0x268,
#endif
    /* type = */ bool (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry,
                                                    Red::gameJournalEntryState aEntryState,
                                                    Red::gameJournalNotifyOption aNotifyOption,
                                                    uint32_t a4),
    /* verified = */ true>();

constexpr auto GetEntryState = Core::RawVFunc<
    /* addr = */ 0x2B0,
    /* type = */ Red::gameJournalEntryState (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry),
    /* verified = */ true>();

constexpr auto GetEntryTimestamp = Core::RawVFunc<
    /* addr = */ 0x2C8,
    /* type = */ uint32_t (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry),
    /* verified = */ true>();
}
