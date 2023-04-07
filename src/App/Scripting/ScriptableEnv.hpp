#pragma once

namespace App
{
struct ScriptableEnv : Red::IScriptable
{
    RTTI_IMPL_TYPEINFO(App::ScriptableEnv);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ScriptableEnv, {
    RTTI_ABSTRACT();
});
