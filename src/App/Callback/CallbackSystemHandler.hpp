#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"
#include "App/Callback/CallbackSystemTarget.hpp"

namespace App
{
enum class CallbackRunMode
{
    Default,
    Once,
    OncePerTarget,
};

enum class CallbackLifetime
{
    Session,
    Forever,
};

struct CallbackSystemHandler : Red::IScriptable
{
public:
    CallbackSystemHandler() = default;

    CallbackSystemHandler(const Red::WeakHandle<Red::IScriptable>& aContext, Red::CName aFunction)
        : contextWeak(aContext)
        , function(aFunction)
    {
    }

    CallbackSystemHandler(Red::CName aContext, Red::CName aFunction)
        : contextType(aContext)
        , function(aFunction)
    {
    }

    void operator()(const Red::Handle<CallbackSystemEvent>& aEvent)
    {
        std::unique_lock _(stateLock);

        if (!valid)
            return;

        if (!targets.empty())
        {
            const auto it =
                std::ranges::find_if(targets, [&aEvent](Red::Handle<CallbackSystemTarget>& aTarget) -> bool {
                    return aTarget->Matches(aEvent);
                });

            if (it == targets.end())
                return;

            valid = ExecuteCallback(aEvent);

            if (!valid)
                return;

            if (runMode == CallbackRunMode::Once)
            {
                valid = false;
            }
            else if (runMode == CallbackRunMode::OncePerTarget)
            {
                targets.erase(it);

                if (targets.empty())
                {
                    valid = false;
                }
            }
        }
        else
        {
            if (targeted)
            {
                valid = false;
                return;
            }

            valid = ExecuteCallback(aEvent);

            if (!valid)
                return;

            if (runMode == CallbackRunMode::Once || runMode == CallbackRunMode::OncePerTarget)
            {
                valid = false;
            }
        }
    }

    [[nodiscard]] bool IsSameContext(const Red::WeakHandle<Red::IScriptable>& aObject)
    {
        return contextWeak.instance == aObject.instance;
    }

    [[nodiscard]] bool IsSameContext(Red::CName aType)
    {
        return contextType = aType;
    }

    [[nodiscard]] bool IsSameCallback(const Red::WeakHandle<Red::IScriptable>& aObject, Red::CName aFunction)
    {
        return contextWeak.instance == aObject.instance && function == aFunction;
    }

    [[nodiscard]] bool IsSameCallback(Red::CName aType, Red::CName aFunction)
    {
        return contextType = aType && function == aFunction;
    }

    [[nodiscard]] bool IsObject() const noexcept
    {
        return contextWeak.instance;
    }

    [[nodiscard]] bool IsStatic() const noexcept
    {
        return contextType;
    }

    [[nodiscard]] bool IsSticky() noexcept
    {
        std::shared_lock _(stateLock);
        return lifetime == CallbackLifetime::Forever;
    }

    [[nodiscard]] bool IsValid() noexcept
    {
        std::shared_lock _(stateLock);
        return valid;
    }

    Red::Handle<CallbackSystemHandler> AddTarget(const Red::Handle<CallbackSystemTarget>& aTarget)
    {
        {
            std::unique_lock _(stateLock);
            targets.push_back(aTarget);
            targeted = true;
        }

        return Red::AsHandle(this);
    }

    Red::Handle<CallbackSystemHandler> RemoveTarget(const Red::Handle<CallbackSystemTarget>& aTarget)
    {
        {
            std::unique_lock _(stateLock);
            std::erase_if(targets, [&aTarget](const Red::Handle<CallbackSystemTarget>& aCandidate) -> bool {
                return aCandidate->Equals(aTarget);
            });
        }

        return Red::AsHandle(this);
    }

    Red::Handle<CallbackSystemHandler> SetRunMode(CallbackRunMode aRunMode)
    {
        {
            std::unique_lock _(stateLock);
            runMode = aRunMode;
        }

        return Red::AsHandle(this);
    }

    Red::Handle<CallbackSystemHandler> SetLifetime(CallbackLifetime aLifetime)
    {
        {
            std::unique_lock _(stateLock);
            lifetime = aLifetime;
        }

        return Red::AsHandle(this);
    }

    void Unregister()
    {
        std::unique_lock _(stateLock);
        valid = false;
    }

private:
    [[nodiscard]] inline bool ExecuteCallback(const Red::Handle<CallbackSystemEvent>& aEvent) const
    {
        if (IsStatic())
        {
            return Red::CallStatic(contextType, function, aEvent);
        }

        if (auto context = contextWeak.Lock())
        {
            return Red::CallVirtual(context, function, aEvent);
        }

        return false;
    }

    Red::WeakHandle<Red::IScriptable> contextWeak;
    Red::CName contextType;
    Red::CName function;

    std::shared_mutex stateLock;
    CallbackRunMode runMode{CallbackRunMode::Default};
    CallbackLifetime lifetime{CallbackLifetime::Session};
    Core::Vector<Red::Handle<CallbackSystemTarget>> targets;
    bool targeted{false};
    bool valid{true};

    RTTI_IMPL_TYPEINFO(App::CallbackSystemHandler);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_ENUM(App::CallbackRunMode);
RTTI_DEFINE_ENUM(App::CallbackLifetime);

RTTI_DEFINE_CLASS(App::CallbackSystemHandler, {
    RTTI_METHOD(AddTarget);
    RTTI_METHOD(RemoveTarget);
    RTTI_METHOD(SetRunMode);
    RTTI_METHOD(SetLifetime);
    RTTI_METHOD(Unregister);
});
