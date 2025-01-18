#pragma once

#include "App/Depot/ResourceToken.hpp"
#include "App/Shared/ResourcePathRegistry.hpp"
#include "Core/Facades/Container.hpp"

namespace App
{
struct ResourceWrapper
{
    inline void LoadPath(const Red::redResourceReferenceScriptToken& aScriptToken)
    {
        reference = aScriptToken.resource.Resolve();
        reference.LoadAsync();
    }

    [[nodiscard]] inline Red::redResourceReferenceScriptToken GetPath() const
    {
        return {reference.path};
    }

    [[nodiscard]] inline uint64_t GetHash() const
    {
        return reference.path;
    }

    [[nodiscard]] inline Red::Handle<ResourceTokenWrapper> GetToken() const
    {
        return ResourceTokenWrapper::FromResRef(reference);
    }

    [[nodiscard]] inline Red::Handle<Red::CResource> GetResource() const
    {
        if (!reference.token || !reference.token->IsFinished() || reference.token->IsFailed())
            return {};

        return reference.token->resource;
    }

    [[nodiscard]] inline bool IsEmpty() const
    {
        return !reference.path;
    }

    [[nodiscard]] inline bool IsLoaded() const
    {
        return reference.token && reference.token->IsLoaded();
    }

    [[nodiscard]] inline bool IsFailed() const
    {
        return reference.token && reference.token->IsFailed();
    }

    inline Red::Variant ToVariant(Red::CName aTypeName)
    {
        auto type = Red::CRTTISystem::Get()->GetType(aTypeName);
        
        if (!type || type->GetType() != Red::ERTTIType::ResourceReference)
            return {};
        
        return {type, &reference};
    }

    inline static ResourceWrapper FromVariant(const Red::Variant& aVariant)
    {
        auto type = aVariant.GetType();

        if (!type || type->GetType() != Red::ERTTIType::ResourceReference)
            return {};

        return {*reinterpret_cast<Red::ResourceReference<>*>(aVariant.GetDataPtr())};
    }

    Red::ResourceReference<> reference;
};

struct ResourceAsyncWrapper
{
    inline void SetPath(const Red::redResourceReferenceScriptToken& aScriptToken)
    {
        reference = aScriptToken.resource;
    }

    [[nodiscard]] inline Red::redResourceReferenceScriptToken GetPath() const
    {
        return {reference};
    }

    [[nodiscard]] inline uint64_t GetHash() const
    {
        return reference.path;
    }

    [[nodiscard]] inline bool IsEmpty() const
    {
        return !reference.path;
    }

    Red::ResourceAsyncReference<> reference;
};

struct ResourceScriptReferenceEx
{
    inline static uint64_t GetHash(const Red::redResourceReferenceScriptToken& aReference)
    {
        return aReference.resource.path;
    }

    inline static Red::CString ToString(const Red::redResourceReferenceScriptToken& aReference)
    {
        return Core::Resolve<ResourcePathRegistry>()->ResolvePath(aReference.resource.path);
    }
};
}

RTTI_DEFINE_CLASS(App::ResourceWrapper, "ResourceRef", {
    RTTI_METHOD(LoadPath);
    RTTI_METHOD(GetPath);
    RTTI_METHOD(GetHash);
    RTTI_METHOD(GetToken);
    RTTI_METHOD(GetResource);
    RTTI_METHOD(IsEmpty);
    RTTI_METHOD(IsLoaded);
    RTTI_METHOD(IsFailed);
    RTTI_METHOD(ToVariant);
    RTTI_METHOD(FromVariant);
});

RTTI_DEFINE_CLASS(App::ResourceAsyncWrapper, "ResourceAsyncRef", {
    RTTI_METHOD(SetPath);
    RTTI_METHOD(GetPath);
    RTTI_METHOD(GetHash);
    RTTI_METHOD(IsEmpty);
});

RTTI_EXPAND_CLASS(Red::redResourceReferenceScriptToken, {
    RTTI_METHOD_FQN(App::ResourceScriptReferenceEx::GetHash);
    RTTI_METHOD_FQN(App::ResourceScriptReferenceEx::ToString);
});
