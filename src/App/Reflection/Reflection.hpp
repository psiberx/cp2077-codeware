#pragma once

#include "ReflectionClass.hpp"
#include "ReflectionEnum.hpp"
#include "ReflectionType.hpp"

namespace
{
Red::ClassLocator<Red::ISerializable> s_serializableType;
Red::ClassLocator<Red::IScriptable> s_scriptableType;
}

namespace App
{
struct Reflection
{
    static Red::Handle<ReflectionType> GetTypeOf(const Red::Variant& aVariant)
    {
        if (aVariant.IsEmpty())
            return {};

        auto type = aVariant.GetType();

        switch (type->GetType())
        {
        case Red::ERTTIType::Class:
            return Red::MakeHandle<ReflectionClass>(reinterpret_cast<Red::CClass*>(type));
        case Red::ERTTIType::Enum:
            return Red::MakeHandle<ReflectionEnum>(reinterpret_cast<Red::CEnum*>(type));
        default:
            return Red::MakeHandle<ReflectionType>(type);
        }
    }

     static Red::Handle<ReflectionClass> GetClassOf(const Red::Variant& aVariant, Red::Optional<bool, true> aActualType)
    {
        if (aVariant.IsEmpty())
            return {};

        Red::CClass* resolvedClass{};
        Red::ScriptInstance resolvedInstance{};
        Red::CBaseRTTIType* declaredType = aVariant.GetType();

        switch (declaredType->GetType())
        {
        case Red::ERTTIType::Class:
        {
            resolvedClass = reinterpret_cast<Red::CClass*>(declaredType);
            resolvedInstance = aVariant.GetDataPtr();
            break;
        }
        case Red::ERTTIType::Handle:
        case Red::ERTTIType::WeakHandle:
        {
            auto handleType = reinterpret_cast<Red::CRTTIHandleType*>(declaredType);
            resolvedClass = reinterpret_cast<Red::CClass*>(handleType->innerType);
            resolvedInstance = reinterpret_cast<Red::Handle<Red::IScriptable>*>(aVariant.GetDataPtr())->instance;
            break;
        }
        default: break;
        }

        if (!resolvedClass)
            return {};

        if (aActualType && resolvedClass->IsA(s_serializableType))
        {
            resolvedClass = reinterpret_cast<Red::ISerializable*>(resolvedInstance)->GetType();
        }

        return Red::MakeHandle<ReflectionClass>(resolvedClass);
    }

    static Red::Handle<ReflectionType> GetType(Red::CName aName)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto type = rtti->GetType(aName);

        if (!type)
            return {};

        switch (type->GetType())
        {
        case Red::ERTTIType::Class:
            return Red::MakeHandle<ReflectionClass>(reinterpret_cast<Red::CClass*>(type));
        case Red::ERTTIType::Enum:
            return Red::MakeHandle<ReflectionEnum>(reinterpret_cast<Red::CEnum*>(type));
        default:
            return Red::MakeHandle<ReflectionType>(type);
        }
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

    static Red::DynArray<Red::Handle<ReflectionType>> GetTypes()
    {
        Red::DynArray<Red::Handle<ReflectionType>> wrappers;

        auto rtti = Red::CRTTISystem::Get();
        rtti->types.ForEach([&wrappers](Red::CName, Red::CBaseRTTIType* aType) {
            wrappers.PushBack(Red::MakeHandle<ReflectionType>(aType));
        });

        return wrappers;
    }

    static Red::DynArray<Red::Handle<ReflectionClass>> GetClasses()
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

    static Red::DynArray<Red::Handle<ReflectionClass>> GetDerivedClasses(Red::CName aBase)
    {
        auto rtti = Red::CRTTISystem::Get();
        auto base = rtti->GetClass(aBase);

        if (!base)
            return {};

        Red::DynArray<Red::Handle<ReflectionClass>> wrappers;
        Red::DynArray<Red::CClass*> classes;
        rtti->GetClasses(base, classes, nullptr, true);

        for (const auto& derived : classes)
        {
            wrappers.PushBack(Red::MakeHandle<ReflectionClass>(derived));
        }

        return wrappers;
    }

    static Red::DynArray<Red::Handle<ReflectionEnum>> GetEnums()
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

    static Red::DynArray<Red::Handle<ReflectionStaticFunc>> GetGlobalFunctions()
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
    RTTI_METHOD(GetTypeOf);
    RTTI_METHOD(GetClassOf);
    RTTI_METHOD(GetType);
    RTTI_METHOD(GetClass);
    RTTI_METHOD(GetEnum);
    RTTI_METHOD(GetGlobalFunction);
    RTTI_METHOD(GetTypes);
    RTTI_METHOD(GetClasses);
    RTTI_METHOD(GetDerivedClasses);
    RTTI_METHOD(GetEnums);
    RTTI_METHOD(GetGlobalFunctions);
});

RTTI_DEFINE_ENUM(Red::ERTTIType);
