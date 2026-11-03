#pragma once

#include "Macros/Framework.hpp"

namespace Red
{
template<typename T>
struct RuntimeSystemMapping : public std::false_type {};

namespace Detail
{
template<typename T>
concept HasRuntimeSystemMapping = RuntimeSystemMapping<T>::value
                                      && RuntimeSystemMapping<T>::offset >= 0
                                      && RuntimeSystemMapping<T>::offset <= 64;
}

#if defined(__APPLE__)
// Defined in macos/MacSupport.cpp. CGameEngine (0x97F209D6) is not mapped on Mac.
::RED4ext::GameInstance* MacGameInstance();

// Defined in macos/MacEngine.cpp (Mac::RuntimeSystemAt).
void* MacRuntimeSystemAt(uint32_t aIndex);

// Defined in macos/MacEngine.cpp (Mac::SystemEnabled). False until the system passed its own verification boot.
bool MacSystemEnabled(const char* aName);

// A game system whose world callbacks need something that is not on Mac yet stays off. Logs once per system.
inline void MacSystemOff(const char* aSystem, const char* aWhy)
{
    static std::atomic<unsigned> s_mask{0};
    static std::atomic<unsigned> s_next{0};
    static const char* s_names[32];
    for (unsigned i = 0; i < s_next.load(); ++i)
    {
        if (s_names[i] == aSystem)
            return;
    }
    const unsigned slot = s_next.fetch_add(1);
    if (slot < 32)
        s_names[slot] = aSystem;
    std::fprintf(stderr, "[cw] not on Mac yet: %s stays off (%s)\n", aSystem, aWhy);
    (void)s_mask;
}
#endif

template<typename T, typename U = T>
requires std::is_base_of_v<IGameSystem, T> && std::is_base_of_v<T, U>
U* GetGameSystem()
{
    static const auto s_type = GetType<T>();
#if defined(__APPLE__)
    auto* gameInstance = MacGameInstance();
    if (!gameInstance)
        return nullptr;
#else
    auto& gameInstance = CGameEngine::Get()->framework->gameInstance;
#endif
    return reinterpret_cast<U*>(gameInstance->GetSystem(s_type));
}

template<typename T, typename U = T>
requires std::is_base_of_v<worldIRuntimeSystem, T> && std::is_base_of_v<T, U> && Detail::HasRuntimeSystemMapping<T>
U* GetRuntimeSystem()
{
#if defined(__APPLE__)
    // R18. The engine comes from the InitEngine hook (Mac::Engine), the scene from framework->unk18; null until both exist.
    return reinterpret_cast<U*>(MacRuntimeSystemAt(RuntimeSystemMapping<T>::offset));
#else
    constexpr auto systemOffset = RuntimeSystemMapping<T>::offset * sizeof(Handle<T>);
    const auto& runtimeSceneAddr = CGameEngine::Get()->framework->unk18;
    return reinterpret_cast<Handle<U>*>(runtimeSceneAddr + systemOffset)->instance;
#endif
}
}
