#pragma once

namespace Raw::CClass
{
constexpr auto CreateInstance = Core::RawFunc<
    /* addr = */ RED4ext::Detail::AddressHashes::CClass_CreateInstance,
    /* type = */ Red::IScriptable* (*)(Red::CClass*, uint32_t, bool)>();
}

namespace Raw::ScriptValidator
{
constexpr auto CompareTypeName = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptValidator_CompareTypeName,
    /* type = */ bool (*)(Red::CName aScriptTypeName, Red::CName aNativeTypeName)>();
}

namespace Raw::ScriptBundle
{
constexpr auto Destruct = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptBundle_dtor,
    /* type = */ void (*)(void* aBundle)>();
}
