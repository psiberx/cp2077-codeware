#include "CallbackSystemController.hpp"

bool App::CallbackSystemController::ActivateEvent(Red::CName aEvent)
{
    if (!m_activeEvents.contains(aEvent))
    {
        m_activeEvents.insert(aEvent);
        OnActivateEvent(aEvent);

        if (!m_initialized)
        {
            OnActivateHook();
            m_initialized = true;
        }
    }

    return true;
}

bool App::CallbackSystemController::DeactivateEvent(Red::CName aEvent)
{
    if (m_activeEvents.contains(aEvent))
    {
        m_activeEvents.erase(aEvent);
        OnDeactivateEvent(aEvent);

        if (m_initialized && m_activeEvents.empty())
        {
            OnDeactivateHook();
            m_initialized = false;
        }
    }

    return true;
}

bool App::CallbackSystemController::IsActiveEvent(Red::CName aEvent)
{
    return m_activeEvents.contains(aEvent);
}
