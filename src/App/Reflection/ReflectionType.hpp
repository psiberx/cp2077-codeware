#pragma once

namespace App
{
struct ReflectionType : Red::IScriptable
{
    ReflectionType() = default;

    explicit ReflectionType(Red::CBaseRTTIType* aType)
        : m_type(aType)
    {
    }

    [[nodiscard]] Red::CName GetName() const
    {
        return m_type->GetName();
    }

    [[nodiscard]] Red::ERTTIType GetMetaType() const
    {
        return m_type->GetType();
    }

    [[nodiscard]] Red::Handle<ReflectionType> GetInnerType() const
    {
        Red::CBaseRTTIType* innerType;

        switch (m_type->GetType())
        {
        case Red::ERTTIType::Array:
        case Red::ERTTIType::FixedArray:
        case Red::ERTTIType::NativeArray:
        case Red::ERTTIType::StaticArray:
        {
            innerType = reinterpret_cast<Red::CRTTIBaseArrayType*>(m_type)->innerType;
            break;
        }
        case Red::ERTTIType::Handle:
        {
            innerType = reinterpret_cast<Red::CRTTIHandleType*>(m_type)->innerType;
            break;
        }
        case Red::ERTTIType::WeakHandle:
        {
            innerType = reinterpret_cast<Red::CRTTIWeakHandleType*>(m_type)->innerType;
            break;
        }
        case Red::ERTTIType::ResourceReference:
        {
            innerType = reinterpret_cast<Red::CRTTIResourceReferenceType*>(m_type)->innerType;
            break;
        }
        case Red::ERTTIType::ResourceAsyncReference:
        {
            innerType = reinterpret_cast<Red::CRTTIResourceAsyncReferenceType*>(m_type)->innerType;
            break;
        }
        case Red::ERTTIType::ScriptReference:
        {
            innerType = reinterpret_cast<Red::CRTTIScriptReferenceType*>(m_type)->innerType;
            break;
        }
        default: return {};
        }

        return Red::MakeHandle<ReflectionType>(innerType);
    }

    [[nodiscard]] Red::Variant MakeInstance() const
    {
        return {m_type};
    }

    Red::CBaseRTTIType* m_type;

    RTTI_IMPL_TYPEINFO(App::ReflectionType);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ReflectionType, {
    RTTI_METHOD(GetName);
    RTTI_METHOD(GetMetaType);
    RTTI_METHOD(GetInnerType);
    RTTI_METHOD(MakeInstance);
});
