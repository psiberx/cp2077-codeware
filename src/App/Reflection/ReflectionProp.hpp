#pragma once

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

    Red::CProperty* m_prop;

    RTTI_IMPL_TYPEINFO(App::ReflectionProp);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};
}

RTTI_DEFINE_CLASS(App::ReflectionProp, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetType);
    RTTI_METHOD(IsNative);
});
