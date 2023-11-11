#pragma once

namespace App
{
struct ResetSecuritySystemNetwork : Red::Event
{
    RTTI_IMPL_TYPEINFO(ResetSecuritySystemNetwork);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResetSecuritySystemNetwork, {
    RTTI_PARENT(Red::Event);
});
