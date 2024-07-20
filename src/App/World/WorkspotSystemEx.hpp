#pragma once

#include "Red/WorkspotSystem.hpp"

namespace App
{
struct WorkspotGameSystemEx : Red::gameWorkspotGameSystem
{
    [[nodiscard]] Red::Handle<Red::workWorkspotInstance> GetWorkspotInstance(Red::EntityID aEntityID) const
    {
        if (auto workspotSystem = Red::GetRuntimeSystem<Red::workWorkspotSystem>())
        {
            auto& instanceLock = Raw::workWorkspotSystem::SpinLock::Ref(workspotSystem);
            auto& instanceMap = Raw::workWorkspotSystem::InstanceMap::Ref(workspotSystem);

            std::shared_lock _(instanceLock);

            if (auto instanceEntry = instanceMap.Get(aEntityID.hash))
            {
                return Red::ToHandle(*instanceEntry);
            }
        }

        return {};
    }
};
}

RTTI_EXPAND_CLASS(Red::workWorkspotInstance, {
    RTTI_PROPERTY(Red::Handle<Red::workWorkspotTree>, 0x60, "tree");
    RTTI_PROPERTY(Red::Handle<Red::workWorkspotResource>, 0x70, "resource");
    RTTI_PROPERTY(Red::CName, 0x110, "animName");
    RTTI_PROPERTY(Red::CName, 0x118, "idleAnim");
    RTTI_PROPERTY(Red::workWorkEntryId, 0x120, "entryId");
});

RTTI_EXPAND_CLASS(Red::gameWorkspotGameSystem, App::WorkspotGameSystemEx, {
    RTTI_METHOD(GetWorkspotInstance);
});
