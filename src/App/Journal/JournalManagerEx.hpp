#pragma once

#include "Red/JournalManager.hpp"

namespace App
{
struct JournalManagerEx : Red::JournalManager
{
    Red::DynArray<Red::WeakHandle<Red::gameJournalEntry>> GetEntries(
        const Red::ScriptRef<Red::gameJournalRequestContext>& aRequest)
    {
        Red::DynArray<Red::WeakHandle<Red::gameJournalEntry>> entries;
        Raw::JournalManager::GetEntries(this, *aRequest.ref, entries);

        return entries;
    }
};
}

RTTI_EXPAND_CLASS(Red::JournalManager, App::JournalManagerEx, {
    RTTI_METHOD(GetEntries);
});
