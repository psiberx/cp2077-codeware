#pragma once

#include "Red/Addresses.hpp"

namespace Raw::Entity
{
constexpr auto GetComponents = Core::RawFunc<
    /* addr = */ Red::Addresses::Entity_GetComponents,
    /* type = */ Red::DynArray<Red::Handle<Red::ent::IComponent>>& (*)(Red::ent::Entity*)>();
}
