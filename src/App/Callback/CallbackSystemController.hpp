#pragma once

namespace App
{
class CallbackSystemController
{
public:
    virtual Core::Map<Red::CName, Red::CName> GetEvents() = 0;
    virtual Core::Map<Red::CName, Red::CName> GetMappings();
    virtual bool ActivateEvent(Red::CName aEvent);
    virtual bool DeactivateEvent(Red::CName aEvent);

protected:
    virtual bool OnActivateHook() = 0;
    virtual bool OnDeactivateHook() = 0;
    virtual void OnActivateEvent(Red::CName aEvent) {}
    virtual void OnDeactivateEvent(Red::CName aEvent) {}

    bool IsActiveEvent(Red::CName aEvent);

private:
    bool m_initialized = false;
    Core::Set<Red::CName> m_activeEvents;
};
}
