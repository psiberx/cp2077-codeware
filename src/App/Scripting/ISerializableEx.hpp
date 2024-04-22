#pragma once

namespace App
{
struct ISerializableEx : Red::ISerializable
{
    bool IsA(Red::CName aClassName)
    {
        return GetNativeType()->IsA(Red::GetClass(aClassName));
    }

    bool IsExactlyA(Red::CName aClassName)
    {
        return GetNativeType()->name == aClassName;
    }
};
}

RTTI_EXPAND_CLASS(Red::ISerializable, App::ISerializableEx, {
    RTTI_METHOD(IsA);
    RTTI_METHOD(IsExactlyA);
});
