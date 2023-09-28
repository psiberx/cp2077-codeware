#pragma once

#include "Addresses.hpp"

namespace Raw::CClass
{
constexpr auto CreateInstance = Core::RawFunc<
    /* addr = */ RED4ext::Addresses::CClass_CreateInstance,
    /* type = */ Red::IScriptable* (*)(Red::CClass*, uint32_t, bool)>();
}

// namespace Raw::IScriptable
// {
// constexpr auto InitializeScriptData = Core::RawFunc<
//     /* addr = */ Red::Addresses::IScriptable_InitializeScriptData,
//     /* type = */ void (*)(Red::IScriptable* aInstance, Red::CClass* aClass, void* aValueHolder)>();
// }

namespace Raw::ScriptValidator
{
constexpr auto CompareTypeName = Core::RawFunc<
    /* addr = */ Red::Addresses::ScriptValidator_CompareTypeName,
    /* type = */ bool (*)(Red::CName aScriptTypeName, Red::CName aNativeTypeName)>();
}

namespace Raw::ScriptBundle
{
constexpr auto Destruct = Core::RawFunc<
    /* addr = */ Red::Addresses::ScriptBundle_dtor,
    /* type = */ void (*)(void* aBundle)>();
}
