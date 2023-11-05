#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
using NodeID = uint16_t;
using QuestNodePath = DynArray<NodeID>;
using NodePathHash = uint32_t;

struct QuestNodeKey
{
    QuestNodeKey() = default;

    QuestNodeKey(NodePathHash aPhaseHash, NodeID aNodeID = 0)
        : phaseHash(aPhaseHash)
        , nodeID(aNodeID)
    {
    }

    QuestNodeKey(const QuestNodePath& aNodePath, NodeID aNodeID = 0)
        : phaseHash(FNV1a32(reinterpret_cast<uint8_t*>(aNodePath.entries), aNodePath.size * sizeof(NodeID)))
        , nodeID(aNodeID)
    {
    }

    operator uint64_t() const noexcept
    {
        return (static_cast<uint64_t>(phaseHash) << 32) + nodeID;
    }

    operator uint32_t() const noexcept
    {
        uint64_t data = *this;
        return FNV1a32(reinterpret_cast<uint8_t*>(&data), sizeof(data));
    }

    NodePathHash phaseHash;
    NodePathHash nodeID;
};
RED4EXT_ASSERT_SIZE(QuestNodeKey, 0x8);
RED4EXT_ASSERT_OFFSET(QuestNodeKey, phaseHash, 0x0);
// RED4EXT_ASSERT_OFFSET(PhaseNodePath, nodeID, 0x6);

struct QuestContext
{
    uint8_t unk0[0xF8];                       // 00
    DynArray<questPhaseInstance*> phaseStack; // F8
    NodeID nodeID;                            // 108
    uint64_t unk110[0x44];                    // 110
};
RED4EXT_ASSERT_SIZE(QuestContext, 0x330);
RED4EXT_ASSERT_OFFSET(QuestContext, phaseStack, 0xF8);

struct QuestNodeSocket
{
    QuestNodeSocket(CName aName = {})
        : name(aName)
        , unk08(0)
    {
    }

    CName name;
    uint8_t unk08;
};

struct FactID
{
    constexpr FactID(uint32_t aHash = 0) noexcept
        : hash(aHash)
    {
    }

    constexpr FactID(const char* aName) noexcept
        : hash(FNV1a32(aName))
    {
    }

    FactID(QuestNodeKey aPath) noexcept
        : hash(aPath)
    {
    }

    uint32_t hash;
};

struct FactStore
{
    uint64_t unk00;
    Red::Map<FactID, int32_t> data;
};

using FactStoreIndex = uint32_t;

struct FactManager
{
    static constexpr FactStoreIndex NamedFactStore = 1;
    static constexpr FactStoreIndex GraphStoreMin = 2;
    static constexpr FactStoreIndex GraphStoreMax = 10;

    virtual ~FactManager() = 0;                                                    // 00
    virtual void sub_08() = 0;                                                     // 08
    virtual int32_t GetFact(FactStoreIndex aStore, FactID aFact) = 0;              // 10
    virtual void SetFact(FactStoreIndex aStore, FactID aFact, int32_t aValue) = 0; // 18

    inline uint32_t GetFact(FactID aFact)
    {
        return GetFact(NamedFactStore, aFact);
    }

    inline void SetFact(FactID aFact, int32_t aValue)
    {
        SetFact(NamedFactStore, aFact, aValue);
    }

    inline void ResetFact(FactID aFact)
    {
        SetFact(NamedFactStore, aFact, 0);
    }

    inline void ResetGraphFact(FactID aFact)
    {
        for (auto store = GraphStoreMin; store <= GraphStoreMax; ++store)
        {
#ifndef NDEBUG
            if (GetFact(store, aFact) != 0)
                __nop();
#endif
            SetFact(store, aFact, 0);
        }
    }

    FactStore* data[11];
};

enum class ESecurityAreaType
{
    DISABLED = 0,
    SAFE = 1,
    RESTRICTED = 2,
    DANGEROUS = 3,
};

enum class ETransitionMode
{
    GENTLE = 0,
    FORCED = 1,
};

struct AreaTypeTransition
{
    ESecurityAreaType transitionTo;
    int32_t transitionHour;
    ETransitionMode transitionMode;
    uint32_t listenerID;
    bool locked;
};
}

namespace Raw::QuestsSystem
{
using FactManager = Core::OffsetPtr<0xF8, Red::FactManager*>;

constexpr auto CreateContext = Core::RawFunc<
    /* addr = */ Red::Addresses::QuestsSystem_CreateContext,
    /* type = */ void* (*)(Red::questIQuestsSystem* aPhase,
                           Red::QuestContext* aContext,
                           int8_t a3 /* = 1 */,
                           int8_t a4 /* = 0 */,
                           int32_t a5 /* = 1000000 */,
                           int32_t a6 /* = -1 */)>();

// constexpr auto StopPhase = Core::RawVFunc<
//     /* addr = */ 0x210,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::PhaseNodePath& aNodePath, uint8_t a2)>();
//
// constexpr auto RestartPhase = Core::RawVFunc<
//     /* addr = */ 0x238,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::PhaseNodePath& aNodePath,
//                                                    const Red::DynArray<Red::CName>& aInputSockets)>();
}

namespace Raw::QuestLoader
{
using PreloadList = Core::OffsetPtr<0x20, Red::DynArray<Red::QuestNodePath>*>;
using SortedPreloadList = Core::OffsetPtr<0x20, Red::SortedArray<Red::QuestNodePath>*>;
using NodePathMap = Core::OffsetPtr<0x48, Red::HashMap<Red::ResourcePath, Red::QuestNodePath>>;

constexpr auto PhasePreloadCheck = Core::RawFunc<
    /* addr = */ Red::Addresses::QuestLoader_PhasePreloadCheck,
    /* type = */ bool (*)(void* aLoader, const Red::QuestNodePath& aPhaseNodePath)>();
}

namespace Raw::QuestPhaseInstance
{
constexpr auto Initialize = Core::RawFunc<
    /* addr = */ Red::Addresses::QuestPhaseInstance_Initialize,
    /* type = */ void* (*)(Red::questPhaseInstance* aPhase,
                           Red::QuestContext& aContext,
                           const Red::Handle<Red::questQuestPhaseResource>& aResource,
                           Red::Handle<Red::questGraphDefinition>& aGraph,
                           const Red::QuestNodePath& aParentPath,
                           Red::NodeID aPhaseNodeID)>();

constexpr auto ExequteGraph = Core::RawFunc<
    /* addr = */ Red::Addresses::QuestPhaseInstance_ExequteGraph,
    /* type = */ uint8_t (*)(Red::questPhaseInstance* aPhase,
                             Red::QuestContext& aContext,
                             const Red::WeakHandle<Red::questNodeDefinition>& aNode,
                             const Red::QuestNodeSocket& aInputSocket,
                             bool a5,
                             const Red::DynArray<Red::QuestNodeSocket>& aOutputSocket)>();

constexpr auto ExecuteNode = Core::RawFunc<
    /* addr = */ Red::Addresses::QuestPhaseInstance_ExecuteNode,
    /* type = */ uint8_t (*)(Red::questPhaseInstance* aPhase,
                             Red::questNodeDefinition* aNode,
                             Red::QuestContext& aContext,
                             const Red::QuestNodeSocket& aInputSocket,
                             const Red::DynArray<Red::QuestNodeSocket>& aOutputSocket)>();
}

namespace Raw::QuestSocketDefinition
{
using OwnerNode = Core::OffsetPtr<0x48, Red::WeakHandle<Red::questNodeDefinition>>;
}

namespace Raw::QuestConditionType
{
using OwnerNodeID = Core::OffsetPtr<0x30, Red::NodePathHash>;
}
