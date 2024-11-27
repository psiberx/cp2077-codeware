#pragma once

namespace Red
{
using JournalEntryHash = uint32_t;
}

namespace Raw::JournalManager
{
constexpr auto GetEntries = Core::RawVFunc<
    /* addr = */ 0x210,
    /* type = */ void* (Red::gameIJournalManager::*)(const Red::gameJournalRequestContext& aRequest,
                                                     Red::DynArray<Red::WeakHandle<Red::gameJournalEntry>>& aOut)>();

constexpr auto GetEntryByHash = Core::RawVFunc<
    /* addr = */ 0x220,
    /* type = */ void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aOut,
                                                     Red::JournalEntryHash aEntryHash)>();

constexpr auto ChangeEntryState = Core::RawVFunc<
    /* addr = */ 0x268,
    /* type = */ bool (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry,
                                                    Red::gameJournalEntryState aEntryState,
                                                    Red::gameJournalNotifyOption aNotifyOption,
                                                    uint32_t a4)>();

constexpr auto GetEntryState = Core::RawVFunc<
    /* addr = */ 0x2B0,
    /* type = */ Red::gameJournalEntryState (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry)>();

constexpr auto GetEntryTimestamp = Core::RawVFunc<
    /* addr = */ 0x2C8,
    /* type = */ uint32_t (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry)>();
}
