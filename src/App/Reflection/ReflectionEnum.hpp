#pragma once

#include "ReflectionType.hpp"

namespace App
{
struct ReflectionConst : Red::IScriptable
{
    ReflectionConst() = default;

    ReflectionConst(Red::CName aName, int64_t aValue)
        : m_name(aName)
        , m_value(aValue)
    {
    }

    [[nodiscard]] Red::CName GetName() const
    {
        return m_name;
    }

    [[nodiscard]] int64_t GetValue() const
    {
        return m_value;
    }

    Red::CName m_name;
    int64_t m_value;

    RTTI_IMPL_TYPEINFO(App::ReflectionConst);
    RTTI_IMPL_ALLOCATOR();
};

struct ReflectionEnum : ReflectionType
{
    ReflectionEnum() = default;

    explicit ReflectionEnum(Red::CEnum* aType)
        : ReflectionType(aType)
        , m_enum(aType)
    {
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionConst>> GetConstants() const
    {
        Red::DynArray<Red::Handle<ReflectionConst>> wrappers;

        for (uint32_t i = 0; i < m_enum->valueList.size; ++i)
        {
            const auto& name = m_enum->hashList[i];
            const auto& value = m_enum->valueList[i];

            wrappers.PushBack(Red::MakeHandle<ReflectionConst>(name, value));
        }

        return wrappers;
    }

    [[nodiscard]] bool IsNative() const
    {
        return !m_enum->flags.isScripted;
    }

    Red::CEnum* m_enum;

    RTTI_IMPL_TYPEINFO(App::ReflectionEnum);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ReflectionConst, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetValue);
});

RTTI_DEFINE_CLASS(App::ReflectionEnum, {
    RTTI_PARENT(App::ReflectionType);
    RTTI_METHOD(GetConstants);
    RTTI_METHOD(IsNative);
});
