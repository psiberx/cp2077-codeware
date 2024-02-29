#pragma once

namespace Red
{
struct PersistentObject
{
    virtual ~PersistentObject() = default;        // 00
    virtual CClass* GetPersistentStateType() = 0; // 08

    Handle<PersistentState> persistentState;
};
RED4EXT_ASSERT_SIZE(PersistentObject, 0x18);

struct PersistentStateParams
{
    game::IPersistencySystem* system; // 00
    bool mergeStates;                 // 08
    CClass* objectType;               // 10
    PersistentID persistentId;        // 18
    uint64_t unk28;                   // 28
};
RED4EXT_ASSERT_SIZE(PersistentStateParams, 0x30);
}

namespace Raw::PersistentObject
{
constexpr auto InitializeState = Core::RawFunc<
    /* addr = */ Red::AddressLib::PersistentObject_InitializeState,
    /* type = */ void (*)(Red::PersistentObject* aObject, Red::PersistentStateParams* aParams)>();
}
