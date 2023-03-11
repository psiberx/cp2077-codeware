#pragma once

namespace Red
{
class RTTIRegistrar
{
public:
    using Callback = void(*)();

    RTTIRegistrar(Callback aRegister, Callback aDescribe);

    void Register();
    static void RegisterPending();

private:
    bool m_registered;
    Callback m_register;
    Callback m_describe;

    static inline std::vector<RTTIRegistrar*> s_pending;
};
}
