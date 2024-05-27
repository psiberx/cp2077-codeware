#pragma once

namespace App
{
struct ResourceHelper
{
    static bool LoadReferenceResource(const Red::Handle<Red::ISerializable>& aOwner, Red::CName aReferencePropName,
                                      const Red::ResourceAsyncReference<>& aResourceAsyncReference)
    {
        if (!aOwner || !aReferencePropName || !aResourceAsyncReference.path)
            return false;

        auto prop = aOwner->GetType()->GetProperty(aReferencePropName);

        if (!prop || prop->type->GetType() != Red::ERTTIType::ResourceReference)
            return false;

        *prop->GetValuePtr<Red::ResourceReference<>>(aOwner) = aResourceAsyncReference.Resolve();
        return true;
    }

    static bool IsReferenceLoaded(const Red::Handle<Red::ISerializable>& aOwner, Red::CName aReferencePropName)
    {
        if (!aOwner || !aReferencePropName)
            return false;

        auto prop = aOwner->GetType()->GetProperty(aReferencePropName);

        if (!prop || prop->type->GetType() != Red::ERTTIType::ResourceReference)
            return false;

        const auto& token = prop->GetValuePtr<Red::ResourceReference<>>(aOwner)->token;

        return token && token->IsLoaded();
    }

    static Red::Handle<Red::CResource> GetReferenceResource(const Red::Handle<Red::ISerializable>& aOwner,
                                                            Red::CName aReferencePropName)
    {
        if (!aOwner || !aReferencePropName)
            return {};

        auto prop = aOwner->GetType()->GetProperty(aReferencePropName);

        if (!prop || prop->type->GetType() != Red::ERTTIType::ResourceReference)
            return {};

        return prop->GetValuePtr<Red::ResourceReference<>>(aOwner)->token->resource;
    }
};
}

RTTI_DEFINE_CLASS(App::ResourceHelper, {
    RTTI_METHOD(LoadReferenceResource);
    RTTI_METHOD(IsReferenceLoaded);
    RTTI_METHOD(GetReferenceResource);
});
