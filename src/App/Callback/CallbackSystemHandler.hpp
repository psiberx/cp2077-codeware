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

    CallbackSystemHandler(Red::CName aEventType, Red::WeakHandle<Red::IScriptable> aContext, Red::CName aFunctionName)
        : eventType(aEventType)
        , contextWeak(std::move(aContext))
        , functionName(aFunctionName)
        , function(Red::GetMemberFunction(contextWeak.Lock(), aFunctionName))
        , valid(function != nullptr)
    {
    }

    CallbackSystemHandler(Red::CName aEventType, Red::CName aContext, Red::CName aFunctionName)
        : eventType(aEventType)
        , contextType(aContext)
        , functionName(aFunctionName)
        , function(Red::GetStaticFunction(contextType, aFunctionName))
        , valid(function != nullptr)
    {
    }

    void operator()(const Red::Handle<CallbackSystemEvent>& aEvent)
    {
        std::unique_lock sync(callbackLock);

        if (!registered || !valid)
            return;

        if (targeted)
        {
            {
                std::unique_lock _(stateLock);

                if (targets.empty())
                    return;

                const auto it =
                    std::ranges::find_if(targets, [&aEvent](Red::Handle<CallbackSystemTarget>& aTarget) -> bool {
                        return aTarget->Matches(aEvent);
                    });

                if (it == targets.end())
                    return;

                if (runMode == CallbackRunMode::Once)
                {
                    targets.clear();
                }
                else if (runMode == CallbackRunMode::OncePerTarget)
                {
                    targets.erase(it);
                }
            }

            valid = ExecuteCallback(aEvent);

            if (!valid)
                return;
        }
        else
        {
            valid = ExecuteCallback(aEvent);

            if (!valid)
                return;

            {
                std::shared_lock _(stateLock);

                if (runMode == CallbackRunMode::Once || runMode == CallbackRunMode::OncePerTarget)
                {
                    registered = false;
                }
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

    [[nodiscard]] bool IsSameCallback(const Red::WeakHandle<Red::IScriptable>& aObject, Red::CName aFunctionName)
    {
        return contextWeak.instance == aObject.instance && functionName == aFunctionName;
    }

    [[nodiscard]] bool IsSameCallback(Red::CName aType, Red::CName aFunctionName)
    {
        return contextType = aType && functionName == aFunctionName;
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

    [[nodiscard]] bool IsRegistered() const
    {
        return registered;
    }

    Red::Handle<CallbackSystemHandler> AddTarget(const Red::Handle<CallbackSystemTarget>& aTarget)
    {
        if (aTarget->Supports(eventType))
        {
            std::unique_lock _(stateLock);
            targets.push_back(aTarget);
            targeted = true;
        }

        return Red::AsHandle(this);
    }

    Red::Handle<CallbackSystemHandler> RemoveTarget(const Red::Handle<CallbackSystemTarget>& aTarget)
    {
        if (aTarget->Supports(eventType))
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
        registered = false;
    }

private:
    [[nodiscard]] inline bool ExecuteCallback(const Red::Handle<CallbackSystemEvent>& aEvent) const
    {
        if (contextType)
        {
            return Red::CallFunction(function, aEvent);
        }

        if (auto context = contextWeak.Lock())
        {
            return Red::CallFunction(context, function, aEvent);
        }

        return false;
    }

    Red::CName eventType;
    Red::WeakHandle<Red::IScriptable> contextWeak;
    Red::CName contextType;
    Red::CName functionName;
    Red::CBaseFunction* function{nullptr};

    Red::SharedSpinLock stateLock;
    CallbackRunMode runMode{CallbackRunMode::Default};
    CallbackLifetime lifetime{CallbackLifetime::Session};
    Core::Vector<Red::Handle<CallbackSystemTarget>> targets;
    bool targeted{false};

    Red::SharedSpinLock callbackLock;
    bool registered{true};
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
    RTTI_METHOD(IsRegistered);
});
