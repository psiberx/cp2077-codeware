#pragma once

#include "ReflectionType.hpp"

namespace App
{
struct ReflectionProp : Red::IScriptable
{
    ReflectionProp() = default;

    explicit ReflectionProp(Red::CProperty* aProp)
        : m_prop(aProp)
    {
    }

    [[nodiscard]] Red::CName GetName() const
    {
        return m_prop->name;
    }

    [[nodiscard]] Red::Handle<ReflectionType> GetType() const
    {
        return Red::MakeHandle<ReflectionType>(m_prop->type);
    }

    [[nodiscard]] bool IsNative() const
    {
        return !m_prop->flags.isScripted;
    }

    Red::Variant GetValue(const Red::Variant& aInstance)
    {
        auto instance = ResolveInstance(aInstance);

        if (!instance)
            return {};

        return {m_prop->type, m_prop->GetValuePtr<void>(instance)};
    }

    void SetValue(const Red::Variant& aInstance, const Red::Variant& aValue)
    {
        if (m_prop->type != aValue.GetType())
            return;

        auto instance = ResolveInstance(aInstance);

        if (!instance)
            return;

        m_prop->SetValue(instance, aValue.GetDataPtr());
    }

    Red::ScriptInstance ResolveInstance(const Red::Variant& aVariant)
    {
        switch (aVariant.GetType()->GetType())
        {
        case Red::ERTTIType::Class:
            return aVariant.GetDataPtr();
        case Red::ERTTIType::Handle:
            return reinterpret_cast<Red::Handle<Red::IScriptable>*>(aVariant.GetDataPtr())->instance;
        case Red::ERTTIType::WeakHandle:
            return reinterpret_cast<Red::WeakHandle<Red::IScriptable>*>(aVariant.GetDataPtr())->instance;
        default:
            return nullptr;
        }
    }

    Red::CProperty* m_prop;

    RTTI_IMPL_TYPEINFO(App::ReflectionProp);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ReflectionProp, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetType);
    RTTI_METHOD(IsNative);
    RTTI_METHOD(GetValue);
    RTTI_METHOD(SetValue);
});
