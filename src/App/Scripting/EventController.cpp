#include "EventController.hpp"

bool App::EventController::ActivateEvent(Red::CName aEvent)
{
    if (!m_activeEvents.contains(aEvent))
    {
        m_activeEvents.insert(aEvent);
        OnActivateEvent(aEvent);

        if (!m_initialized)
        {
            Initialize();
            m_initialized = true;
        }
    }

    return true;
}

bool App::EventController::DeactivateEvent(Red::CName aEvent)
{
    if (m_activeEvents.contains(aEvent))
    {
        m_activeEvents.erase(aEvent);
        OnDeactivateEvent(aEvent);

        if (m_initialized && m_activeEvents.empty())
        {
            Uninitialize();
            m_initialized = false;
        }
    }

    return true;
}

bool App::EventController::IsActiveEvent(Red::CName aEvent)
{
    return m_activeEvents.contains(aEvent);
}
