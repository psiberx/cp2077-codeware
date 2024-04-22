#pragma once

namespace App
{
struct ScriptableService : Red::IScriptable
{
    static Red::Handle<ScriptableService> Get(Red::CName aName);

    RTTI_IMPL_TYPEINFO(App::ScriptableService);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ScriptableService, {
    RTTI_ABSTRACT();
    RTTI_METHOD(Get);
});
