#pragma once

namespace App
{
struct ResourceTokenWrapper : Red::SelfHandle<ResourceTokenWrapper>, Red::IScriptable
{
    ResourceTokenWrapper() = default;

    ResourceTokenWrapper(Red::SharedPtr<Red::ResourceToken<Red::CResource>> aToken)
        : m_token(std::move(aToken))
    {
    }

    [[nodiscard]] Red::Handle<Red::CResource> GetResource() const
    {
        return m_token->Get();
    }

    [[nodiscard]] Red::RaRef<Red::CResource> GetPath() const
    {
        return {m_token->path};
    }

    [[nodiscard]] uint64_t GetHash() const
    {
        return m_token->path;
    }

    [[nodiscard]] bool IsFinished() const
    {
        return m_token->IsFinished();
    }

    [[nodiscard]] bool IsLoaded() const
    {
        return m_token->IsLoaded();
    }

    [[nodiscard]] bool IsFailed() const
    {
        return m_token->IsFailed();
    }

    void RegisterCallback(const Red::Handle<Red::IScriptable>& aListener, Red::CName aCallback)
    {
        auto& weakToken = *reinterpret_cast<Red::WeakHandle<ResourceTokenWrapper>*>(&ref);

        if (IsFinished())
        {
            Red::CallVirtual(aListener, aCallback, weakToken);
        }
        else
        {
            m_token->OnLoaded([weakToken, weakListener = Red::WeakHandle(aListener), aCallback](Red::Handle<Red::CResource>&) {
                if (!weakToken.Expired() && !weakListener.Expired())
                {
                    Red::CallVirtual(weakListener.Lock(), aCallback, &weakToken);
                }
            });
        }
    }

    Red::SharedPtr<Red::ResourceToken<Red::CResource>> m_token;

    RTTI_IMPL_TYPEINFO(App::ResourceTokenWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceTokenWrapper, "ResourceToken", {
    RTTI_METHOD(GetResource);
    RTTI_METHOD(GetPath);
    RTTI_METHOD(GetHash);
    RTTI_METHOD(IsFinished);
    RTTI_METHOD(IsLoaded);
    RTTI_METHOD(IsFailed);
    RTTI_METHOD(RegisterCallback);
});
