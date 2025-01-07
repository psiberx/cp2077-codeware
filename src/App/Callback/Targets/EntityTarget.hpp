#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/EntityBuilderEvent.hpp"
#include "App/Callback/Events/EntityComponentEvent.hpp"
#include "App/Callback/Events/EntityLifecycleEvent.hpp"
#include "App/Callback/Events/VehicleLightControlEvent.hpp"
#include "Red/Puppet.hpp"
#include "Red/Vehicle.hpp"

namespace App
{
struct EntityTarget : CallbackSystemTarget
{
    EntityTarget() = default;

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        switch (aEvent->GetType()->GetName())
        {
        case Red::GetTypeName<EntityBuilderEvent>():
        {
            auto* builder = aEvent.GetPtr<EntityBuilderEvent>()->entityBuilder->builder.instance;

            if (entityID && builder->request && entityID != builder->request->entityID)
                return false;

            if (entityType)
            {
                if (!builder->entityExtractor)
                    return false;

                auto rootIndex = builder->entityTemplate->compiledDataHeader.rootIndex;

                if (rootIndex < 0)
                    return false;

                if (!builder->entityExtractor->results[rootIndex]->GetType()->IsA(entityType))
                    return false;
            }

            if (templatePath && templatePath != builder->entityTemplate->path)
                return false;

            if (appearanceName && builder->request && appearanceName != builder->request->appearanceName)
                return false;

            if (recordID && builder->request && recordID != builder->request->recordID)
                return false;

            if (appearancePath)
            {
                if (builder->appearance.resource)
                {
                    if (appearancePath != builder->appearance.resource->path)
                        return false;

                    if (definitionName && definitionName != builder->appearance.definition->name)
                        return false;
                }
                else if (builder->appearances.size != 0)
                {
                    auto match = false;

                    for (const auto& appearance : builder->appearances)
                    {
                        if (appearancePath != appearance.resource->path)
                            continue;

                        if (definitionName && definitionName != appearance.definition->name)
                            continue;

                        match = true;
                        break;
                    }

                    if (!match)
                        return false;
                }
                else
                {
                    return false;
                }
            }

            break;
        }
        case Red::GetTypeName<EntityLifecycleEvent>():
        case Red::GetTypeName<EntityComponentEvent>():
        case Red::GetTypeName<VehicleLightControlEvent>():
        {
            auto* entity = aEvent.GetPtr<EntityLifecycleEvent>()->entity.instance;

            if (appearancePath || definitionName)
                return false;

            if (entityID && entityID != entity->entityID)
                return false;

            if (entityType && !entity->GetType()->IsA(entityType))
                return false;

            if (templatePath && templatePath != entity->templatePath)
                return false;

            if (appearanceName && appearanceName != entity->appearanceName)
                return false;

            if (recordID)
            {
                if (auto puppet = Red::Cast<Red::gamePuppetBase>(entity))
                {
                    if (recordID != Raw::Puppet::RecordID::Ref(entity))
                        return false;
                }
                else if (auto vehicle = Red::Cast<Red::vehicleBaseObject>(entity))
                {
                    if (recordID != Raw::Vehicle::RecordID::Ref(entity))
                        return false;
                }
                else if (auto device = Red::Cast<Red::gameDeviceBase>(entity))
                {
                    auto controller = Red::GetPropertyPtr<Red::Handle<Red::gameComponent>>(device, "controller");
                    if (!controller || !*controller)
                        return false;

                    auto& ps = (*controller)->persistentState;
                    if (!ps)
                        return false;

                    auto deviceID = Red::GetPropertyPtr<Red::TweakDBID>(ps, "tweakDBRecord");
                    if (!deviceID || recordID != *deviceID)
                        return false;
                }
                else
                {
                    return false;
                }
            }

            break;
        }
        }

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<EntityTarget>();

        return entityID == target->entityID && entityType == target->entityType &&
               templatePath == target->templatePath && appearanceName == target->appearanceName;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<EntityBuilderEvent>() ||
               aEventType == Red::GetTypeName<EntityLifecycleEvent>() ||
               aEventType == Red::GetTypeName<EntityComponentEvent>() ||
               aEventType == Red::GetTypeName<VehicleLightControlEvent>();
    }

    static Red::Handle<EntityTarget> ID(Red::EntityID aEntityID)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->entityID = aEntityID;

        return target;
    }

    static Red::Handle<EntityTarget> Type(Red::CName aEntityType)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->entityType = Red::GetClass(aEntityType);

        return target;
    }

    static Red::Handle<EntityTarget> RecordID(Red::TweakDBID aRecordID)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->recordID = aRecordID;

        return target;
    }

    static Red::Handle<EntityTarget> Template(const Red::RaRef<>& aTemplate)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->templatePath = aTemplate.path;

        return target;
    }

    static Red::Handle<EntityTarget> Appearance(Red::CName aAppearance)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->appearanceName = aAppearance;

        return target;
    }

    static Red::Handle<EntityTarget> Definition(const Red::RaRef<>& aResource, Red::Optional<Red::CName> aName)
    {
        auto target = Red::MakeHandle<EntityTarget>();
        target->appearancePath = aResource.path;
        target->definitionName = aName;

        return target;
    }

    Red::EntityID entityID{};
    Red::CClass* entityType{};
    Red::TweakDBID recordID{};
    Red::ResourcePath templatePath{};
    Red::CName appearanceName{};
    Red::ResourcePath appearancePath{};
    Red::CName definitionName{};

    RTTI_IMPL_TYPEINFO(App::EntityTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(ID);
    RTTI_METHOD(Type);
    RTTI_METHOD(RecordID);
    RTTI_METHOD(Template);
    RTTI_METHOD(Appearance);
    RTTI_METHOD(Definition);
});
