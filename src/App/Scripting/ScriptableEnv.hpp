#pragma once

namespace App
{
struct ScriptableEnv : Red::IScriptable
{
    static Red::Handle<ScriptableEnv> Get(Red::CName aName);

    RTTI_IMPL_TYPEINFO(App::ScriptableEnv);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ScriptableEnv, {
    RTTI_ABSTRACT();
    RTTI_METHOD(Get);
});
