#pragma once

#include "ReflectionProp.hpp"
#include "ReflectionType.hpp"

namespace App
{
struct ReflectionFunc : Red::IScriptable
{
    ReflectionFunc() = default;

    explicit ReflectionFunc(Red::CBaseFunction* aFunc)
        : m_func(aFunc)
    {
    }

    [[nodiscard]] Red::CName GetName() const
    {
        return m_func->shortName;
    }

    [[nodiscard]] Red::CName GetFullName() const
    {
        return m_func->fullName;
    }

    [[nodiscard]] Red::Handle<ReflectionType> GetReturnType() const
    {
        if (!m_func->returnType)
            return {};

        return Red::MakeHandle<ReflectionType>(m_func->returnType->type);
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionProp>> GetParameters() const
    {
        Red::DynArray<Red::Handle<ReflectionProp>> wrappers;

        for (const auto& prop : m_func->params)
        {
            wrappers.PushBack(Red::MakeHandle<ReflectionProp>(prop));
        }

        return wrappers;
    }

    [[nodiscard]] bool IsNative() const
    {
        return m_func->flags.isNative;
    }

    [[nodiscard]] bool IsStatic() const
    {
        return m_func->flags.isStatic;
    }

    Red::Variant Call(Red::IScriptable* aContext,
                      Red::Optional<Red::DynArray<Red::Variant>>& aArgs,
                      Red::Optional<Red::ScriptRef<bool>>& aStatus,
                      Red::CStackFrame* aFrame) const
    {
        Red::Variant ret;

        if (aArgs->size != m_func->params.size)
        {
            if (aStatus)
            {
                aStatus = false;
            }

            return ret;
        }

        if (!m_func->flags.isStatic)
        {
            const auto& func = reinterpret_cast<Red::CClassFunction*>(m_func);

            if (!aContext || !aContext->GetType()->IsA(func->parent))
            {
                if (aStatus)
                {
                    aStatus = false;
                }

                return ret;
            }
        }

        Red::StackArgs_t args(m_func->params.size);
        Red::CStackType result;
        Red::CStack stack(aContext, args.data(), args.size(), &result);

        for (uint32_t i = 0; i < m_func->params.size; ++i)
        {
            if (!Red::IsCompatible(m_func->params[i]->type, aArgs->entries[i].GetType(), aArgs->entries[i].GetDataPtr()))
            {
                if (aStatus)
                {
                    aStatus = false;
                }

                return ret;
            }

            stack.args[i].type = aArgs->entries[i].GetType();
            stack.args[i].value = aArgs->entries[i].GetDataPtr();
        }

        if (m_func->returnType)
        {
            ret.Init(m_func->returnType->type);

            stack.result->type = ret.GetType();
            stack.result->value = ret.GetDataPtr();
        }

        const auto success = Red::CallFunction(aFrame, m_func, stack);

        if (aStatus)
        {
            aStatus = success;
        }

        return ret;
    }

    Red::CBaseFunction* m_func;

    RTTI_IMPL_TYPEINFO(App::ReflectionFunc);
    RTTI_IMPL_ALLOCATOR();
};

struct ReflectionMemberFunc : ReflectionFunc
{
    using ReflectionFunc::ReflectionFunc;

    Red::Variant Call(const Red::Handle<Red::IScriptable>& aContext,
                      Red::Optional<Red::DynArray<Red::Variant>>& aArgs,
                      Red::Optional<Red::ScriptRef<bool>>& aStatus,
                      Red::CStackFrame* aFrame)
    {
        return ReflectionFunc::Call(aContext.GetPtr(), aArgs, aStatus, aFrame);
    }

    RTTI_IMPL_TYPEINFO(App::ReflectionMemberFunc);
    RTTI_IMPL_ALLOCATOR();
};

struct ReflectionStaticFunc : ReflectionFunc
{
    using ReflectionFunc::ReflectionFunc;

    Red::Variant Call(Red::Optional<Red::DynArray<Red::Variant>>& aArgs,
                      Red::Optional<Red::ScriptRef<bool>>& aStatus,
                      Red::CStackFrame* aFrame)
    {
        return ReflectionFunc::Call(nullptr, aArgs, aStatus, aFrame);
    }

    RTTI_IMPL_TYPEINFO(App::ReflectionStaticFunc);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ReflectionFunc, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetFullName);
    RTTI_METHOD(GetReturnType);
    RTTI_METHOD(GetParameters);
    RTTI_METHOD(IsNative);
    RTTI_METHOD(IsStatic);
});

RTTI_DEFINE_CLASS(App::ReflectionMemberFunc, {
    RTTI_PARENT(App::ReflectionFunc);
    RTTI_METHOD(Call);
});

RTTI_DEFINE_CLASS(App::ReflectionStaticFunc, {
    RTTI_PARENT(App::ReflectionFunc);
    RTTI_METHOD(Call);
});
