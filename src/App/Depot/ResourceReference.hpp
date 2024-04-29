#pragma once

#include "App/Depot/ResourcePathRegistry.hpp"
#include "App/Depot/ResourceToken.hpp"
#include "Core/Facades/Container.hpp"

namespace App
{
struct ResourceWrapper
{
    void LoadPath(const Red::redResourceReferenceScriptToken& aScriptToken)
    {
        resource = aScriptToken.resource.Resolve();
        resource.LoadAsync();
    }

    [[nodiscard]] Red::redResourceReferenceScriptToken GetPath() const
    {
        return {resource.path};
    }

    [[nodiscard]] uint64_t GetHash() const
    {
        return resource.path;
    }

    [[nodiscard]] Red::Handle<ResourceTokenWrapper> GetToken() const
    {
        return ResourceTokenWrapper::FromResRef(resource);
    }

    [[nodiscard]] Red::Handle<Red::CResource> GetResource() const
    {
        if (!resource.token || !resource.token->IsFinished() || !resource.token->IsFailed())
            return {};

        return resource.token->resource;
    }

    [[nodiscard]] bool IsEmpty() const
    {
        return !resource.path;
    }

    [[nodiscard]] bool IsLoaded() const
    {
        return resource.token && resource.token->IsLoaded();
    }

    [[nodiscard]] bool IsFailed() const
    {
        return resource.token && resource.token->IsFailed();
    }

    Red::ResourceReference<> resource;
};

struct ResourceAsyncWrapper
{
    void SetPath(const Red::redResourceReferenceScriptToken& aScriptToken)
    {
        resource = aScriptToken.resource;
    }

    [[nodiscard]] Red::redResourceReferenceScriptToken GetPath() const
    {
        return {resource};
    }

    [[nodiscard]] uint64_t GetHash() const
    {
        return resource.path;
    }

    [[nodiscard]] bool IsEmpty() const
    {
        return !resource.path;
    }

    Red::ResourceAsyncReference<> resource;
};

struct ResourceScriptReferenceEx
{
    inline static uint64_t GetHash(const Red::redResourceReferenceScriptToken& aReference)
    {
        return aReference.resource.path;
    }

    inline static Red::CString ToString(const Red::redResourceReferenceScriptToken& aReference)
    {
        return Core::Resolve<ResourcePathRegistry>()->GetPath(aReference.resource.path);
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
