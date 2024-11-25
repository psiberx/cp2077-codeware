#pragma once

#include "Red/EntityBuilder.hpp"

namespace App
{
struct EntityBuilderTemplateWrapper : Red::IScriptable
{
    EntityBuilderTemplateWrapper() = default;

    EntityBuilderTemplateWrapper(Red::WeakPtr<Red::EntityBuilder> aBuilder)
        : builder(std::move(aBuilder))
    {
    }

    [[nodiscard]] Red::Handle<Red::entEntityTemplate> GetResource() const
    {
        return builder.instance->entityTemplate;
    }

    [[nodiscard]] Red::CName GetAppearanceName() const
    {
        if (!builder.instance->request)
            return {};

        return builder.instance->request->appearanceName;
    }

    [[nodiscard]] Red::Handle<Red::entEntity> GetEntity() const
    {
        if (!builder.instance->entityExtractor || builder.instance->entityExtractor->results.size == 0)
            return {};

        auto rootIndex = builder.instance->entityTemplate->compiledDataHeader.rootIndex;

        if (rootIndex < 0)
            return {};

        return Red::Cast<Red::entEntity>(builder.instance->entityExtractor->results[rootIndex]);
    }

    [[nodiscard]] Red::DynArray<Red::Handle<Red::IComponent>> GetComponents() const
    {
        if (!builder.instance->entityExtractor || builder.instance->entityExtractor->results.size == 0)
            return {};

        Red::DynArray<Red::Handle<Red::IComponent>> components;

        auto rootIndex = builder.instance->entityTemplate->compiledDataHeader.rootIndex;
        for (auto i = rootIndex + 1; i < builder.instance->entityExtractor->results.size; ++i)
        {
            components.PushBack(Red::Cast<Red::IComponent>(builder.instance->entityExtractor->results[i]));
        }

        return components;
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent) const
    {
        if (!builder.instance->entityExtractor)
            return;

        builder.instance->entityExtractor->results.PushBack(aComponent);
    }

    Red::WeakPtr<Red::EntityBuilder> builder;

    RTTI_IMPL_TYPEINFO(App::EntityBuilderTemplateWrapper);
    RTTI_IMPL_ALLOCATOR();
};

struct EntityBuilderAppearanceWrapper : Red::IScriptable
{
    EntityBuilderAppearanceWrapper() = default;

    EntityBuilderAppearanceWrapper(Red::WeakPtr<Red::EntityBuilder> aBuilder, Red::EntityBuilderAppearance* aAppearance)
        : builder(std::move(aBuilder))
        , appearance(aAppearance)
    {
    }

    [[nodiscard]] Red::Handle<Red::appearanceAppearanceResource> GetResource() const
    {
        if (!appearance)
            return {};

        return appearance->resource;
    }

    [[nodiscard]] Red::Handle<Red::appearanceAppearanceDefinition> GetDefinition() const
    {
        if (!appearance)
            return {};

        return appearance->definition;
    }

    [[nodiscard]] Red::DynArray<Red::Handle<Red::IComponent>> GetComponents() const
    {
        if (!appearance)
            return {};

        Red::DynArray<Red::Handle<Red::IComponent>> components;

        for (auto i = 0; i < appearance->extractor->results.size; ++i)
        {
            components.PushBack(Red::Cast<Red::IComponent>(appearance->extractor->results[i]));
        }

        return components;
    }

    void AddComponent(const Red::Handle<Red::IComponent>& aComponent) const
    {
        if (!appearance)
            return;

        appearance->extractor->results.PushBack(aComponent);
    }

    Red::WeakPtr<Red::EntityBuilder> builder;
    Red::EntityBuilderAppearance* appearance{nullptr};

    RTTI_IMPL_TYPEINFO(App::EntityBuilderAppearanceWrapper);
    RTTI_IMPL_ALLOCATOR();
};

struct EntityBuilderWrapper : Red::IScriptable
{
    EntityBuilderWrapper() = default;

    EntityBuilderWrapper(Red::WeakPtr<Red::EntityBuilder> aBuilder)
        : builder(std::move(aBuilder))
    {
    }

    [[nodiscard]] Red::TweakDBID GetRecordID() const
    {
        if (!builder.instance->request)
            return {};

        return builder.instance->request->recordID;
    }

    [[nodiscard]] Red::ResourceAsyncReference<> GetTemplatePath() const
    {
        return builder.instance->entityTemplate->path;
    }

    [[nodiscard]] Red::CName GetAppearanceName() const
    {
        if (!builder.instance->request)
            return {};

        return builder.instance->request->appearanceName;
    }

    [[nodiscard]] Red::EntityID GetEntityID() const
    {
        if (!builder.instance->request)
            return {};

        return builder.instance->request->entityID;
    }

    [[nodiscard]] Red::CName GetEntityType() const
    {
        if (!builder.instance->entityExtractor || builder.instance->entityExtractor->results.size == 0)
            return {};

        auto rootIndex = builder.instance->entityTemplate->compiledDataHeader.rootIndex;

        if (rootIndex < 0)
            return {};

        return builder.instance->entityExtractor->results[rootIndex]->GetType()->GetName();
    }

    [[nodiscard]] Red::Handle<Red::entEntityParametersStorage> GetEntityParams() const
    {
        if (!builder.instance->request)
            return {};

        return builder.instance->request->entityParams;
    }

    [[nodiscard]] Red::Handle<EntityBuilderTemplateWrapper> GetTemplate() const
    {
        return Red::MakeHandle<EntityBuilderTemplateWrapper>(builder);
    }

    [[nodiscard]] Red::Handle<EntityBuilderAppearanceWrapper> GetAppearance() const
    {
        if (!builder.instance->appearance.resource)
            return {};

        return Red::MakeHandle<EntityBuilderAppearanceWrapper>(builder, &builder.instance->appearance);
    }

    [[nodiscard]] Red::DynArray<Red::Handle<EntityBuilderAppearanceWrapper>> GetCustomAppearances() const
    {
        Red::DynArray<Red::Handle<EntityBuilderAppearanceWrapper>> appearances;

        for (auto i = 0; i < builder.instance->appearances.size; ++i)
        {
            appearances.PushBack(Red::MakeHandle<EntityBuilderAppearanceWrapper>(builder,
                                                                                 &builder.instance->appearances[i]));
        }

        return appearances;
    }

    [[nodiscard]] bool HasEntity() const
    {
        return builder.instance->entityExtractor;
    }

    [[nodiscard]] bool HasAppearance() const
    {
        return builder.instance->appearance.resource;
    }

    [[nodiscard]] bool HasCustomAppearances() const
    {
        return builder.instance->appearances.size != 0;
    }

    Red::WeakPtr<Red::EntityBuilder> builder;

    RTTI_IMPL_TYPEINFO(App::EntityBuilderWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::EntityBuilderWrapper, {
     RTTI_METHOD(GetRecordID);
     RTTI_METHOD(GetTemplatePath);
     RTTI_METHOD(GetAppearanceName);
     RTTI_METHOD(GetEntityID);
     RTTI_METHOD(GetEntityType);
     RTTI_METHOD(GetEntityParams);
     RTTI_METHOD(GetTemplate);
     RTTI_METHOD(GetAppearance);
     RTTI_METHOD(GetCustomAppearances);
     RTTI_METHOD(HasEntity);
     RTTI_METHOD(HasAppearance);
     RTTI_METHOD(HasCustomAppearances);
});

RTTI_DEFINE_CLASS(App::EntityBuilderTemplateWrapper, {
    RTTI_METHOD(GetResource);
    RTTI_METHOD(GetAppearanceName);
    RTTI_METHOD(GetEntity);
    RTTI_METHOD(GetComponents);
    RTTI_METHOD(AddComponent);
});

RTTI_DEFINE_CLASS(App::EntityBuilderAppearanceWrapper, {
    RTTI_METHOD(GetResource);
    RTTI_METHOD(GetDefinition);
    RTTI_METHOD(GetComponents);
    RTTI_METHOD(AddComponent);
});
