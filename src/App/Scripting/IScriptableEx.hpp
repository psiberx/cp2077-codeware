#pragma once

#include "Red/Scripting.hpp"

namespace App
{
struct IScriptableEx : Red::IScriptable
{
    Red::Handle<Red::IScriptable> Clone()
    {
        Red::Handle<Red::IScriptable> clone;
        Raw::ISerializable::Clone(clone, Red::ToHandle(this));
        return clone;
    }
};
}

RTTI_EXPAND_CLASS(Red::IScriptable, App::IScriptableEx, {
    RTTI_METHOD(Clone);
});
