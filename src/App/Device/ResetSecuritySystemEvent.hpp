#pragma once

namespace App
{
struct ResetSecuritySystem : Red::Event
{
    RTTI_IMPL_TYPEINFO(ResetSecuritySystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResetSecuritySystem, {
    RTTI_PARENT(Red::Event);
});
