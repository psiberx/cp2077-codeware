#pragma once

namespace App
{
struct ScriptableService : Red::IScriptable
{
    RTTI_IMPL_TYPEINFO(App::ScriptableService);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ScriptableService, {
    RTTI_ABSTRACT();
});
