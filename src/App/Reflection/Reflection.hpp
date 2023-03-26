#pragma once

#include "ReflectionClass.hpp"
#include "ReflectionEnum.hpp"
#include "ReflectionType.hpp"

namespace App
{
struct Reflection
{
    static Red::Handle<ReflectionType> ResolveType(Red::Variant& aVariant)
    {
        if (aVariant.IsEmpty())
            return {};

        return Red::MakeHandle<ReflectionType>(aVariant.GetType());
    }

    static Red::Handle<ReflectionType> GetType(Red::CName aName)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto type = rtti->GetType(aName);

        if (!type)
            return {};

        return Red::MakeHandle<ReflectionType>(type);
    }

    static Red::Handle<ReflectionClass> GetClass(Red::CName aName)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto type = rtti->GetClass(aName);

        if (!type)
            return {};

        return Red::MakeHandle<ReflectionClass>(type);
    }

    static Red::Handle<ReflectionEnum> GetEnum(Red::CName aName)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto type = rtti->GetEnum(aName);

        if (!type)
            return {};

        return Red::MakeHandle<ReflectionEnum>(type);
    }

    static Red::Handle<ReflectionStaticFunc> GetGlobalFunction(Red::CName aName)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto func = rtti->GetFunction(aName);

        if (!func)
            return {};

        return Red::MakeHandle<ReflectionStaticFunc>(func);
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionType>> GetTypes() const
    {
        Red::DynArray<Red::Handle<ReflectionType>> wrappers;

        auto rtti = Red::CRTTISystem::Get();
        rtti->types.ForEach([&wrappers](Red::CName, Red::CBaseRTTIType* aType) {
            wrappers.PushBack(Red::MakeHandle<ReflectionType>(aType));
        });

        return wrappers;
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionClass>> GetClasses() const
    {
        Red::DynArray<Red::Handle<ReflectionClass>> wrappers;

        auto rtti = Red::CRTTISystem::Get();
        rtti->types.ForEach([&wrappers](Red::CName, Red::CBaseRTTIType* aType) {
            if (aType->GetType() == Red::ERTTIType::Class)
            {
                wrappers.PushBack(Red::MakeHandle<ReflectionClass>(reinterpret_cast<Red::CClass*>(aType)));
            }
        });

        return wrappers;
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionEnum>> GetEnums() const
    {
        Red::DynArray<Red::Handle<ReflectionEnum>> wrappers;

        auto rtti = Red::CRTTISystem::Get();
        rtti->types.ForEach([&wrappers](Red::CName, Red::CBaseRTTIType* aType) {
            if (aType->GetType() == Red::ERTTIType::Enum)
            {
                wrappers.PushBack(Red::MakeHandle<ReflectionEnum>(reinterpret_cast<Red::CEnum*>(aType)));
            }
        });

        return wrappers;
    }

    [[nodiscard]] Red::DynArray<Red::Handle<ReflectionStaticFunc>> GetGlobalFunctions() const
    {
        Red::DynArray<Red::Handle<ReflectionStaticFunc>> wrappers;

        auto rtti = Red::CRTTISystem::Get();
        rtti->funcs.ForEach([&wrappers](Red::CName, Red::CGlobalFunction* aFunc) {
            wrappers.PushBack(Red::MakeHandle<ReflectionStaticFunc>(aFunc));
        });

        return wrappers;
    }
};
}

RTTI_DEFINE_CLASS(App::Reflection, {
    RTTI_METHOD(ResolveType);
    RTTI_METHOD(GetType);
    RTTI_METHOD(GetClass);
    RTTI_METHOD(GetEnum);
    RTTI_METHOD(GetGlobalFunction);
    RTTI_METHOD(GetTypes);
    RTTI_METHOD(GetClasses);
    RTTI_METHOD(GetEnums);
    RTTI_METHOD(GetGlobalFunctions);
});

RTTI_DEFINE_ENUM(Red::ERTTIType);
