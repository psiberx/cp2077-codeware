#pragma once

#if defined(__APPLE__)
#include "MacHookChain.hpp"
#endif

namespace Red
{
template<CName N, typename T, typename... Args>
inline T* AcquireSharedInstance(Args&&... args)
{
#if defined(__APPLE__)
    // macOS: the instance is shared with the other plugins (ArchiveXL) through exported functions (macos/MacHookChain.cpp), not
    // through the game's CRTTISystem, whose Mac layout has no typesLock or unkF8 slot (see the struct offset notes in macos/NOT_YET.md).
    // The first plugin to publish a name keeps the instance.
    if (auto* shared = Mac::Shared::Acquire(N.hash, sizeof(T)))
        return static_cast<T*>(shared);

    static const auto s_localInstance = std::make_unique<T>(std::forward<Args>(args)...);
    Mac::Shared::Publish(N.hash, sizeof(T), s_localInstance.get());
    return s_localInstance.get();
#else
    constexpr CName SharedName = FNV1a64("!", N);

    auto rtti = Red::CRTTISystem::Get();
    if (!rtti)
         return nullptr;

    auto* mutex = const_cast<SharedSpinLock*>(reinterpret_cast<volatile SharedSpinLock*>(&rtti->typesLock));
    auto* storage = reinterpret_cast<HashMap<CName, T*>*>(&rtti->unkF8);

    std::lock_guard _(*mutex);

    auto* entry = storage->Get(SharedName);
    if (entry)
         return *entry;

    static const auto s_instance = std::make_unique<T>(std::forward<Args>(args)...);
    storage->Insert(SharedName, s_instance.get());

    return s_instance.get();
#endif
}
}
