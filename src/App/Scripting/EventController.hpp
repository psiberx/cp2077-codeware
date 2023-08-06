#pragma once

namespace App
{
class EventController
{
public:
    virtual Core::Vector<Red::CName> GetEvents() = 0;
    virtual bool ActivateEvent(Red::CName aEvent);
    virtual bool DeactivateEvent(Red::CName aEvent);

protected:
    virtual bool Initialize() = 0;
    virtual bool Uninitialize() = 0;
    virtual void OnActivateEvent(Red::CName aEvent) {}
    virtual void OnDeactivateEvent(Red::CName aEvent) {}

    bool IsActiveEvent(Red::CName aEvent);

private:
    bool m_initialized = false;
    Core::Set<Red::CName> m_activeEvents;
};
}
