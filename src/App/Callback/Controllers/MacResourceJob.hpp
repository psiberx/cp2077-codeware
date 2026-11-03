#pragma once

// R13. Body of the Mac resource hooks. ResourceLoadHook hooks job 0x2257548 and ResourcePostLoadHook
// hooks job 0x2257830. In both, captures[0] is the ResourceSerializer*. The list at +0x230 is
// complete and not yet handed on, so the callbacks see every resource of the batch.
// No job group: the job body is already the right moment, and the mods never call GetJobGroup().

#if defined(__APPLE__)

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "App/Callback/MacHookStats.hpp"
#include "Red/Serialization.hpp"
#include "MacDiag.hpp"
#include "MacR13.hpp"

#include <cstdio>

namespace App
{
inline void DispatchMacResourceJob(Red::ResourceSerializer** aCaptures, Red::CName aEventName,
                                   MacHookStats::Counters& aStats, bool aIsLoad)
{
    aStats.calls.fetch_add(1, std::memory_order_relaxed);

    try
    {
        auto* serializer = aCaptures ? *aCaptures : nullptr;
        if (!serializer || serializer->serializables.IsEmpty())
            return;

        // The hooks start at plugin load, before the CallbackSystem class is registered.
        // CallbackSystem::Get() would build the system early, so wait until it exists.
        const bool ready = CallbackSystem::Exists();
        if (!ready)
        {
            aStats.noSystem.fetch_add(1, std::memory_order_relaxed);
        }

        for (const auto& serializable : serializer->serializables)
        {
            if (const auto& resource = Red::Cast<Red::CResource>(serializable))
            {
                const uint64_t pathHash = resource->path.hash;
                // DIAG R80: the LizziesBDs sector whose old-format instanced mesh node over-reads (R79 crash).
                if (aIsLoad && pathHash == 0x550364e813d7a12aull && Mac::DiagEnabled())
                {
                    Mac::LogSectorNodes(resource.instance, pathHash);
                }
                if (aIsLoad)
                {
                    Mac::NoteInstancedMeshSector(resource.instance, pathHash); // R82
                }
                MacHookStats::NoteResource(aStats, pathHash);
                MacHookStats::NoteAudioTarget(pathHash, aIsLoad);

                bool reached = false;
                if (ready && CallbackSystem::Get()->DispatchNativeEvent<ResourceEvent>(aEventName, resource))
                {
                    reached = true;
                    aStats.dispatched.fetch_add(1, std::memory_order_relaxed);
                }
                MacHookStats::NoteLizzieTarget(pathHash, aIsLoad, reached); // DIAG R14
            }
        }
    }
    catch (...)
    {
        static std::atomic<bool> s_logged{false};
        if (!s_logged.exchange(true))
        {
            std::fprintf(stderr, "[cw] resource hook exception (event %s)\n", aIsLoad ? "Resource/Load" : "Resource/PostLoad");
        }
    }
}
}

#endif
