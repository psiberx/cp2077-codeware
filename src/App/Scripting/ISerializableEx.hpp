#pragma once

#include "Red/Scripting.hpp"

namespace App
{
struct ISerializableEx : Red::ISerializable
{
    Red::CName GetClassName()
    {
        return GetNativeType()->name;
    }

    bool IsA(Red::CName aClassName)
    {
        return GetNativeType()->IsA(Red::GetClass(aClassName));
    }

    bool IsExactlyA(Red::CName aClassName)
    {
        return GetNativeType()->name == aClassName;
    }

    Red::Handle<Red::ISerializable> Clone()
    {
        Red::Handle<Red::ISerializable> clone;
        Raw::ISerializable::Clone(clone, Red::ToHandle(this));
        return clone;
    }
};
}

RTTI_EXPAND_CLASS(Red::ISerializable, App::ISerializableEx, {
    RTTI_METHOD(GetClassName, "GetClassName");
    RTTI_METHOD(IsA);
    RTTI_METHOD(IsExactlyA);
    RTTI_METHOD(Clone);
});
