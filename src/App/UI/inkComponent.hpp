#pragma once

#include "Red/InkCore.hpp"

namespace App
{
struct inkComponent : Red::inkLogicController
{
    void OnConstruct()
    {
        auto self = Red::ToHandle(this);

        Red::Handle<Red::inkWidget> root;
        Red::CallVirtual(this, "OnCreate", root);

        if (root)
        {
            root->logicController = self;
            detached = root;
            widget = root;
        }
    }

    void OnInitialize() override
    {
        detached.Reset();

        Raw::inkLogicController::OnInitialize(this);
    }

    void OnUninitialize() override
    {
        Raw::inkLogicController::OnUninitialize(this);
    }

    void OnArrangeChildrenComplete() override
    {
        Raw::inkLogicController::OnArrangeChildrenComplete(this);
    }

    bool IsAttached()
    {
        return widget && !detached;
    }

    Red::Handle<Red::inkWidget> detached;

    RTTI_IMPL_TYPEINFO(inkComponent);
};
}

RTTI_DEFINE_CLASS(App::inkComponent, {
    RTTI_ABSTRACT();
    RTTI_PARENT(Red::inkLogicController);
    RTTI_CALLBACK(OnConstruct);
    RTTI_METHOD(IsAttached);
});
