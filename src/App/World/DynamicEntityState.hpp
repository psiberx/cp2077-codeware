#pragma once

#include "App/World/DynamicEntitySpec.hpp"

#if defined(__APPLE__)
#include <utility>
#include "MacDiag.hpp"
#endif

namespace App
{
#if defined(__APPLE__)
// macOS (R34): the SDK gives EntityStub no allocator type on the Mac, so Codeware cannot own a stub through UniquePtr. This holder keeps
// the pointer, hands it on with Release() (DespawnFromEntityState passes it to IEntityStubSystem::DeleteStub, which takes it over), and
// never frees it: a stub that would be destroyed here is left to the game with a MAC_DIAG line (the R33 world-detach hand-off goes
// through Release() before that). The Mac game destroys stubs with its own destructor and frees them into PoolGMPL_PS; ADDRESS_CHECK.md.
class MacEntityStubRef
{
public:
    MacEntityStubRef() = default;
    MacEntityStubRef(Red::EntityStub* aStub) noexcept
        : m_stub(aStub)
    {
    }
    MacEntityStubRef(const MacEntityStubRef&) = delete;
    MacEntityStubRef& operator=(const MacEntityStubRef&) = delete;
    MacEntityStubRef(MacEntityStubRef&& aOther) noexcept
        : m_stub(std::exchange(aOther.m_stub, nullptr))
    {
    }
    MacEntityStubRef& operator=(MacEntityStubRef&& aOther) noexcept
    {
        if (this != &aOther)
        {
            Leave();
            m_stub = std::exchange(aOther.m_stub, nullptr);
        }
        return *this;
    }
    ~MacEntityStubRef()
    {
        Leave();
    }

    explicit operator bool() const noexcept
    {
        return m_stub != nullptr;
    }

    Red::EntityStub* Release() noexcept
    {
        return std::exchange(m_stub, nullptr);
    }

private:
    void Leave() noexcept
    {
        if (m_stub)
        {
            MAC_DIAG("[cw] DynamicEntityState: a stub (%p) left to the game instead of being freed by Codeware\n",
                     static_cast<void*>(m_stub));
            m_stub = nullptr;
        }
    }

    Red::EntityStub* m_stub = nullptr;
};
using EntityStubHolder = MacEntityStubRef;
#else
using EntityStubHolder = Red::UniquePtr<Red::EntityStub>;
#endif

struct DynamicEntityState : Red::IScriptable
{
    DynamicEntityState() = default;

    DynamicEntityState(Red::EntityID aEntityId, Red::Handle<DynamicEntitySpec> aEntitySpec)
        : entityID(aEntityId)
        , entitySpec(std::move(aEntitySpec))
        , deleted(false)
    {
    }

    void AcquireStub(Red::EntityStubTokenPtr& aToken)
    {
        std::unique_lock _(entityLock);
        entityStub = aToken->ExtractStub();
    }

    EntityStubHolder ExtractStub()
    {
        std::unique_lock _(entityLock);
        return std::move(entityStub);
    }

    Red::EntityID entityID; // Never changes after state creation or restoration
    Red::Handle<DynamicEntitySpec> entitySpec;
    EntityStubHolder entityStub;
    Red::SharedSpinLock entityLock; // For stub, active and deleted statuses
    bool deleted;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityState);
    RTTI_IMPL_ALLOCATOR();
};

using DynamicEntityStatePtr = Red::Handle<DynamicEntityState>;
}

RTTI_DEFINE_CLASS(App::DynamicEntityState, {
    RTTI_PERSISTENT(entityID);
    RTTI_PERSISTENT(entitySpec);
});
