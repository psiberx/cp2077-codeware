#pragma once

#include "DynamicEntityState.hpp"

namespace App
{
struct DynamicEntitySystemPS : Red::PersistentState
{
    Red::DynArray<DynamicEntityStatePtr> m_entityStates;

    RTTI_IMPL_TYPEINFO(App::DynamicEntitySystemPS);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::DynamicEntitySystemPS, {
    RTTI_PARENT(Red::PersistentState);
    RTTI_PERSISTENT(m_entityStates);
});
