#pragma once

namespace Red
{
using QuestNodeID = uint16_t;
using QuestNodePath = DynArray<QuestNodeID>;
using QuestNodePathHash = uint32_t;

inline bool IsRelatedQuestNodePath(const QuestNodePath& aParentPath, const QuestNodePath& aPath)
{
    return aPath.size > aParentPath.size &&
           std::memcmp(aPath.entries, aParentPath.entries, aParentPath.size * sizeof(Red::QuestNodeID)) == 0;
}

inline QuestNodePathHash MakeQuestNodePathHash(const QuestNodePath& aNodePath, int32_t aLength = 0)
{
    if (aLength == 0)
    {
        aLength = static_cast<int32_t>(aNodePath.size);
    }
    else if (aLength < 0)
    {
        aLength += static_cast<int32_t>(aNodePath.size);
    }

    return FNV1a32(reinterpret_cast<uint8_t*>(aNodePath.entries), aLength * sizeof(QuestNodeID));
}

struct QuestNodeKey
{
    QuestNodeKey() = default;

    QuestNodeKey(QuestNodePathHash aPhaseHash, QuestNodeID aNodeID = 0)
        : phaseHash(aPhaseHash)
        , nodeID(aNodeID)
    {
    }

    QuestNodeKey(const QuestNodePath& aNodePath)
        : phaseHash(MakeQuestNodePathHash(aNodePath, -1))
        , nodeID(aNodePath.Back())
    {
    }

    QuestNodeKey(const QuestNodePath& aNodePath, QuestNodeID aNodeID)
        : phaseHash(MakeQuestNodePathHash(aNodePath))
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

    QuestNodePathHash phaseHash;
    QuestNodePathHash nodeID;
};
RED4EXT_ASSERT_SIZE(QuestNodeKey, 0x8);
RED4EXT_ASSERT_OFFSET(QuestNodeKey, phaseHash, 0x0);
RED4EXT_ASSERT_OFFSET(QuestNodeKey, nodeID, 0x4);

struct QuestPhaseContext
{
    virtual ~QuestPhaseContext() = default;

    uintptr_t game;              // 08
    uintptr_t unk1;              // 10
    uintptr_t unk2;              // 18
    uintptr_t unk3;              // 20
    uintptr_t unk4;              // 28
    void* prefabLoader;          // 30
    uint8_t unk38[0x230 - 0x38]; // 38
};
RED4EXT_ASSERT_SIZE(QuestPhaseContext, 0x230);

struct QuestContext
{
    uint8_t unk0[0xF8];                       // 00
    DynArray<questPhaseInstance*> phaseStack; // F8
    QuestNodeID nodeID;                       // 108
    QuestPhaseContext phaseContext;           // 110
};
RED4EXT_ASSERT_SIZE(QuestContext, 0x340);
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

struct QuestPhaseHandler
{
    virtual Memory::IAllocator* GetAllocator() = 0;
    virtual ~QuestPhaseHandler() = 0;
    virtual void Initialize(QuestPhaseContext* aContext) = 0;
    virtual void Reinitialize(QuestPhaseContext* aContext) = 0;
    virtual void Uninitialize(QuestPhaseContext* aContext) = 0;
};

struct FactID
{
    constexpr FactID() = default;

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

    operator uint32_t() const noexcept
    {
        return hash;
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
#ifndef NDEBUG
        if (GetFact(NamedFactStore, aFact) != 0)
            __nop();
#endif
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
using Mutex = Core::OffsetPtr<0x60, Red::SharedSpinLock>;
using RootPhase = Core::OffsetPtr<0x68, Red::Handle<Red::questPhaseInstance>>;
using NodePathHashMap = Core::OffsetPtr<0x78, Red::HashMap<Red::QuestNodePathHash, Red::QuestNodePath>>;
using FactManager = Core::OffsetPtr<0xF8, Red::FactManager*>;

constexpr auto CreateContext = Core::RawFunc<
    /* addr = */ Red::AddressLib::QuestsSystem_CreateContext,
    /* type = */ void* (*)(Red::questIQuestsSystem* aPhase,
                           Red::QuestContext* aContext,
                           int32_t a3 /* = 1 */,
                           int8_t a4 /* = 0 */,
                           int32_t a5 /* = 1000000 */,
                           int32_t a6 /* = -1 */)>();

// constexpr auto StopPhase = Core::RawVFunc<
//     /* addr = */ 0x210,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::QuestNodeKey& aNodeKey, uint8_t a2)>();

// constexpr auto PreparePhase = Core::RawVFunc<
//     /* addr = */ 0x228,
//     /* type = */ bool (Red::questIQuestsSystem::*)(const Red::QuestNodeKey& aNodeKey)>();

// constexpr auto RestartPhase = Core::RawVFunc<
//     /* addr = */ 0x238,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::QuestNodeKey& aNodeKey,
//                                                    const Red::DynArray<Red::CName>& aInputSockets)>();
}

namespace Raw::QuestLoader
{
using PreloadList = Core::OffsetPtr<0x20, Red::DynArray<Red::QuestNodePath>*>;
using SortedPreloadList = Core::OffsetPtr<0x20, Red::SortedArray<Red::QuestNodePath>*>;
using NodePathMap = Core::OffsetPtr<0x48, Red::HashMap<Red::ResourcePath, Red::QuestNodePath>>;

constexpr auto PhasePreloadCheck = Core::RawFunc<
    /* addr = */ Red::AddressLib::QuestLoader_PhasePreloadCheck,
    /* type = */ bool (*)(void* aLoader, const Red::QuestNodePath& aPhaseNodePath)>();
}

namespace Raw::QuestPhaseInstance
{
using Resource = Core::OffsetPtr<0x30, Red::Handle<Red::questQuestPhaseResource>>;
using Graph = Core::OffsetPtr<0x40, Red::Handle<Red::questGraphDefinition>>;
using NodePath = Core::OffsetPtr<0x70, Red::QuestNodePath>;
using NodePathHash = Core::OffsetPtr<0x80, Red::QuestNodePathHash>;
using Children = Core::OffsetPtr<0x88, Red::DynArray<Red::Handle<Red::questPhaseInstance>>>;
using Handlers = Core::OffsetPtr<0x98, Red::HashMap<Red::QuestNodePathHash, Red::SharedPtr<Red::QuestPhaseHandler>>>;

constexpr auto Initialize = Core::RawFunc<
    /* addr = */ Red::AddressLib::QuestPhaseInstance_Initialize,
    /* type = */ void* (*)(Red::questPhaseInstance* aPhase,
                           Red::QuestContext& aContext,
                           const Red::Handle<Red::questQuestPhaseResource>& aResource,
                           Red::Handle<Red::questGraphDefinition>& aGraph,
                           const Red::QuestNodePath& aParentPath,
                           Red::QuestNodeID aPhaseNodeID)>();

constexpr auto ExecuteGraph = Core::RawFunc<
    /* addr = */ Red::AddressLib::QuestPhaseInstance_ExecuteGraph,
    /* type = */ uint8_t (*)(Red::questPhaseInstance* aPhase,
                             Red::QuestContext& aContext,
                             const Red::WeakHandle<Red::questNodeDefinition>& aInputNode,
                             const Red::QuestNodeSocket& aInputSocket,
                             bool a5,
                             Red::DynArray<Red::QuestNodeSocket>& aOutputSockets)>();

constexpr auto ExecuteNode = Core::RawFunc<
    /* addr = */ Red::AddressLib::QuestPhaseInstance_ExecuteNode,
    /* type = */ uint8_t (*)(Red::questPhaseInstance* aPhase,
                             Red::questNodeDefinition* aInputNode,
                             Red::QuestContext& aContext,
                             const Red::QuestNodeSocket& aInputSocket,
                             Red::DynArray<Red::QuestNodeSocket>& aOutputSockets)>();

constexpr auto ExecutePath = Core::RawVFunc<
    /* addr = */ 0x120,
    /* type = */ uint8_t (Red::questPhaseInstance::*)(Red::QuestContext& aContext,
                                                      const Red::QuestNodePath& aPhaseNodePath,
                                                      Red::QuestNodeID aInputNodeID,
                                                      Red::CName aInputSocketName,
                                                      Red::DynArray<Red::QuestNodeSocket>& aOutputSockets)>();
}

namespace Raw::QuestSocketDefinition
{
using OwnerNode = Core::OffsetPtr<0x48, Red::WeakHandle<Red::questNodeDefinition>>;
}

namespace Raw::QuestConditionType
{
using OwnerNodeID = Core::OffsetPtr<0x30, Red::QuestNodePathHash>;
}
