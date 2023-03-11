#include "Registrar.hpp"

Red::RTTIRegistrar::RTTIRegistrar(Callback aRegister, Callback aDescribe)
    : m_registered(false)
    , m_register(aRegister)
    , m_describe(aDescribe)
{
    s_pending.push_back(this);
}

void Red::RTTIRegistrar::Register()
{
    if (!m_registered)
    {
        auto* rtti = CRTTISystem::Get();

        if (m_register)
            rtti->AddRegisterCallback(m_register);

        if (m_describe)
            rtti->AddPostRegisterCallback(m_describe);

        m_registered = true;
    }
}

void Red::RTTIRegistrar::RegisterPending()
{
    for (const auto& pending : s_pending)
        pending->Register();

    s_pending.clear();
}
