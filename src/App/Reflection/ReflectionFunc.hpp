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

    Red::CBaseFunction* m_func;

    RTTI_IMPL_TYPEINFO(App::ReflectionFunc);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};

struct ReflectionMemberFunc : ReflectionFunc
{
    using ReflectionFunc::ReflectionFunc;

    RTTI_IMPL_TYPEINFO(App::ReflectionMemberFunc);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};

struct ReflectionStaticFunc : ReflectionFunc
{
    using ReflectionFunc::ReflectionFunc;

    RTTI_IMPL_TYPEINFO(App::ReflectionMemberFunc);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
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
});

RTTI_DEFINE_CLASS(App::ReflectionStaticFunc, {
    RTTI_PARENT(App::ReflectionFunc);
});
