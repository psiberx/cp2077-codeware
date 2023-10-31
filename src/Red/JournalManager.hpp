#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
using JournalEntryHash = uint32_t;
}

namespace Raw::JournalManager
{
constexpr auto GetEntryByHash = Core::RawVFunc<
    /* addr = */ 0x218,
    /* type = */ void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aOut,
                                                     Red::JournalEntryHash aEntryHash)>();

constexpr auto ChangeEntryState = Core::RawVFunc<
    /* addr = */ 0x260,
    /* type = */ void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry,
                                                     Red::gameJournalEntryState aEntryState,
                                                     Red::gameJournalNotifyOption aNotifyOption,
                                                     uint32_t a4)>();

constexpr auto GetEntryState = Core::RawVFunc<
    /* addr = */ 0x2A8,
    /* type = */ Red::gameJournalEntryState (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry)>();

constexpr auto GetEntryTimestamp = Core::RawVFunc<
    /* addr = */ 0x2C0,
    /* type = */ uint32_t (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry>& aEntry)>();
}
