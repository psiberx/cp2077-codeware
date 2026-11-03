// R82. A worldInstancedMeshNode instance attaches only when its mesh index is inside the node's mesh list.
//
// Game 2.5 keeps a worldInstancedMeshNode's meshes in a list at +0x70 (0x40-byte entries: pointer +0x70, capacity +0x78, size
// +0x7c; the mesh resource path at entry +0x20). Each worldInstancedMeshNodeInstance gets the index of its entry from its setup
// record (setup +0x80 -> instance +0x88, in the generic attach +0x1bbf9f4), and its own attach (+0x1b1f1c8, slot 0x168 of the
// instance vtable +0x78e53f0) reads entry[index] +0x20 without a bounds check. (2.3.1 read one mesh path at node +0x80 and returned
// false when it was null.)
//
// An old-format (version 1) node of a mod sector built for an earlier game version comes out of the 2.5 reader with an empty mesh
// list (R80: one bounds entry, then two empty lists), and its old setup record can hold 0xFFFFFFFF at +0x80. An empty DynArray keeps
// its allocator's vtable in the entries pointer, so the read lands at that vtable + 0x3FFFFFFFC0 + 0x20 and the streaming worker
// takes a SIGBUS. That is the Ghost Town crash at the Sunset Motel (2026-10-30, twice): pc +0x1b1f268, x9 = 0xFFFFFFFF,
// x8 = +0x78fbd20 (the allocator vtable) + 0x3FFFFFFFC0, x21 = the worldInstancedMeshNode class.
//
// For an index outside the list the hook returns false, which is what the game's attach returns for a node without a mesh path: the
// attach job releases the instance and marks the node as not attached. Such a node shows nothing; the 2.5 reader has already dropped
// a version 1 node's mesh, so it could not show it anyway. NoteInstancedMeshSector names, once per sector, the loaded sectors that
// hold such nodes, so a skip in the log can be traced to its mod.

#include "MacR13.hpp"
#include "MacDiag.hpp"
#include "MacEngine.hpp"

#include "Core/Hooking/HookingAgent.hpp"

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <mutex>
#include <unordered_set>

namespace Raw::WorldInstancedMeshNodeInstance
{
// +0x1b1f1c8: bool(worldInstancedMeshNodeInstance*, attach context*). Reached only through the instance vtable (slot 0x168).
constexpr auto Attach = Core::RawFunc<
    /* addr = */ Red::AddressLib::WorldInstancedMeshNodeInstance_MacAttach,
    /* type = */ bool (*)(void* aInstance, void* aContext)>();
}

namespace
{
constexpr uintptr_t InstanceNodeOffset = 0x60;      // Handle<worldNode>
constexpr uintptr_t InstanceMeshIndexOffset = 0x88; // uint32
constexpr uintptr_t NodeMeshListOffset = 0x70;      // pointer, capacity (u32), size (u32)
constexpr uintptr_t NodeBoundsCountOffset = 0x6c;
constexpr uintptr_t NodeMeshCountOffset = 0x7c;
constexpr uintptr_t NodeThirdCountOffset = 0x8c;
constexpr uintptr_t NodeVersionOffset = 0x90;
constexpr uintptr_t InstanceSetup58Offset = 0x80;   // the qword the generic attach copies from setup +0x58

// The streaming sector's node setups (DataBuffer) at +0x40, setup version +0x68, node handles at +0x70 (0x10 each), count +0x7c (R80).
constexpr uintptr_t SectorSetupVersionOffset = 0x68;
constexpr uintptr_t SectorNodesOffset = 0x70;
constexpr uintptr_t SectorNodeCountOffset = 0x7c;
constexpr uintptr_t HandleSize = 0x10;

constexpr uint64_t DetailedLogs = 32;

std::atomic<uint64_t> s_skipped{0};

template<typename T>
T Field(const void* aObject, uintptr_t aOffset)
{
    return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(aObject) + aOffset);
}

// Looked up on first use (the RTTI system exists by the time anything streams); a miss is retried, not cached.
Red::CClass* CachedClass(std::atomic<Red::CClass*>& aCache, Red::CName aName)
{
    auto* cls = aCache.load(std::memory_order_acquire);
    if (!cls)
    {
        cls = Red::GetClass(aName);
        aCache.store(cls, std::memory_order_release);
    }
    return cls;
}

Red::CClass* InstancedMeshNodeClass()
{
    static std::atomic<Red::CClass*> s_class{nullptr};
    return CachedClass(s_class, "worldInstancedMeshNode");
}

Red::CClass* StreamingSectorClass()
{
    static std::atomic<Red::CClass*> s_class{nullptr};
    return CachedClass(s_class, "worldStreamingSector");
}

bool IsInstancedMeshNode(const Red::ISerializable* aNode)
{
    auto* nodeClass = InstancedMeshNodeClass();
    if (!aNode || !nodeClass)
    {
        return false;
    }
    auto* type = const_cast<Red::ISerializable*>(aNode)->GetType();
    return type && type->IsA(nodeClass);
}

class InstancedMeshGuard : public Core::HookingAgent
{
public:
    static bool Install()
    {
        const bool ok = IsHooked<Raw::WorldInstancedMeshNodeInstance::Attach>() ||
                        HookWrap<Raw::WorldInstancedMeshNodeInstance::Attach>(&OnAttach);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s InstancedMeshGuard target=%p\n", ok ? "installed" : "FAILED",
                        reinterpret_cast<void*>(Raw::WorldInstancedMeshNodeInstance::Attach.GetOriginalAddress()));
        return ok;
    }

private:
    static bool OnAttach(bool (*aOriginal)(void*, void*), void* aInstance, void* aContext)
    {
        if (aInstance)
        {
            const auto* node = Field<const Red::ISerializable*>(aInstance, InstanceNodeOffset);
            if (IsInstancedMeshNode(node))
            {
                const auto index = Field<uint32_t>(aInstance, InstanceMeshIndexOffset);
                const auto meshes = Field<uint32_t>(node, NodeMeshCountOffset);
                if (index >= meshes)
                {
                    LogSkip(aInstance, node, index, meshes);
                    return false;
                }
            }
        }
        return aOriginal(aInstance, aContext);
    }

    static void LogSkip(const void* aInstance, const Red::ISerializable* aNode, uint32_t aIndex, uint32_t aMeshes)
    {
        const auto n = s_skipped.fetch_add(1, std::memory_order_relaxed) + 1;
        if (n > DetailedLogs && (n % 1024) != 0)
        {
            return;
        }
        std::fprintf(stderr,
                     "[cw] R82 instanced mesh node %p (version %u, lists %u/%u/%u, mesh list %p) instance %p: mesh index 0x%x is "
                     "outside the %u mesh entries, not attached (setup58=0x%llx, skipped %llu)\n",
                     static_cast<const void*>(aNode), static_cast<unsigned>(Field<uint8_t>(aNode, NodeVersionOffset)),
                     Field<uint32_t>(aNode, NodeBoundsCountOffset), aMeshes, Field<uint32_t>(aNode, NodeThirdCountOffset),
                     Field<const void*>(aNode, NodeMeshListOffset), aInstance, aIndex, aMeshes,
                     static_cast<unsigned long long>(Field<uint64_t>(aInstance, InstanceSetup58Offset)),
                     static_cast<unsigned long long>(n));
    }
};
}

bool Mac::InstallInstancedMeshGuard()
{
    return InstancedMeshGuard::Install();
}

unsigned long long Mac::InstancedMeshInstancesSkipped()
{
    return s_skipped.load(std::memory_order_relaxed);
}

void Mac::NoteInstancedMeshSector(void* aResource, unsigned long long aPathHash)
{
    auto* sectorClass = StreamingSectorClass();
    auto* resource = static_cast<Red::ISerializable*>(aResource);
    if (!resource || !sectorClass)
    {
        return;
    }
    auto* type = resource->GetType();
    if (!type || !type->IsA(sectorClass))
    {
        return;
    }

    const auto* nodes = Field<const uint8_t*>(resource, SectorNodesOffset);
    const auto count = Field<uint32_t>(resource, SectorNodeCountOffset);
    uint32_t instanced = 0;
    uint32_t oldFormat = 0;
    uint32_t noMesh = 0;
    for (uint32_t i = 0; i < count; ++i)
    {
        const auto* node = Field<const Red::ISerializable*>(nodes, HandleSize * i);
        if (!IsInstancedMeshNode(node))
        {
            continue;
        }
        ++instanced;
        oldFormat += Field<uint8_t>(node, NodeVersionOffset) < 2 ? 1 : 0;
        noMesh += Field<uint32_t>(node, NodeMeshCountOffset) == 0 ? 1 : 0;
    }
    if (!oldFormat && !noMesh)
    {
        return;
    }

    static std::mutex s_mutex;
    static std::unordered_set<unsigned long long> s_noted;
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        if (!s_noted.insert(aPathHash).second)
        {
            return;
        }
    }
    std::fprintf(stderr,
                 "[cw] R82 sector 0x%016llx (setup version 0x%x, %u nodes): %u worldInstancedMeshNode, %u of them version 1, "
                 "%u with no mesh entry; R82 keeps their instances from attaching\n",
                 aPathHash, Field<uint32_t>(resource, SectorSetupVersionOffset), count, instanced, oldFormat, noMesh);
}
