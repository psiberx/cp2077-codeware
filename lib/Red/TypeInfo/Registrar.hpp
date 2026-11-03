#pragma once

#include <atomic>

#if defined(__APPLE__)
#include <pthread.h>
#endif

namespace Red
{
class TypeInfoRegistrar
{
public:
    using Callback = void(*)();

    TypeInfoRegistrar(Callback aRegister, Callback aDescribe)
    {
        AddRegisterCallback(aRegister);
        AddDescribeCallback(aDescribe);
    }

    static inline void RegisterDiscovered()
    {
        // Called at plugin bootstrap, on the game's main thread.
        s_mainThread = CurrentThreadId();
        QueuePendingRegisterCallbacks();
        QueuePendingDescribeCallbacks();
    }

    // Run the queued RedLib callbacks on this thread. macOS calls this from
    // codeware_registerNatives and again from codeware_postLoadScripts.
    static inline void RunPending()
    {
        ProcessPendingRegisterCallbacks();
        ProcessPendingDescriberCallbacks();
    }

    static inline std::size_t PendingRegisterCount()
    {
        return s_registerCallbacks.size();
    }

    static inline std::size_t PendingDescribeCount()
    {
        return s_describeCallbacks.size();
    }

    static inline void AddRegisterCallback(Callback aRegister)
    {
        if (aRegister)
        {
            s_registerCallbacks.push_back(aRegister);
        }
    }

    static inline void AddDescribeCallback(Callback aDescribe)
    {
        if (aDescribe)
        {
            s_describeCallbacks.push_back(aDescribe);
        }
    }

    static inline bool IsMainThread()
    {
        const auto mainThread = s_mainThread.load();
        return mainThread == 0 || mainThread == CurrentThreadId();
    }

private:
    static inline uint32_t CurrentThreadId()
    {
#if defined(__APPLE__)
        // macOS: the mach thread port of the calling thread stands in for GetCurrentThreadId().
        return static_cast<uint32_t>(pthread_mach_thread_np(pthread_self()));
#else
        return GetCurrentThreadId();
#endif
    }

    static inline void QueuePendingRegisterCallbacks()
    {
        if (!s_registerCallbacks.empty())
        {
            CRTTISystem::Get()->AddRegisterCallback(&OnRegister);
        }
    }

    static inline void QueuePendingDescribeCallbacks()
    {
        if (!s_describeCallbacks.empty())
        {
            CRTTISystem::Get()->AddPostRegisterCallback(&OnDescribe);
        }
    }

    static inline void ProcessPendingRegisterCallbacks()
    {
        auto callbacks = std::move(s_registerCallbacks);
        for (const auto& callback :callbacks)
        {
            callback();
        }
    }

    static inline void ProcessPendingDescriberCallbacks()
    {
        auto callbacks = std::move(s_describeCallbacks);
        for (const auto& callback :callbacks)
        {
            callback();
        }
    }

    static inline void OnRegister()
    {
        ProcessPendingRegisterCallbacks();
        QueuePendingRegisterCallbacks();
    }

    static inline void OnDescribe()
    {
        ProcessPendingDescriberCallbacks();
        QueuePendingDescribeCallbacks();
    }

    static inline std::vector<Callback> s_registerCallbacks;
    static inline std::vector<Callback> s_describeCallbacks;
    static inline std::atomic<uint32_t> s_mainThread{0};
};
}
