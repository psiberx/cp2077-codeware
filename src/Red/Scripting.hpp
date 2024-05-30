#pragma once

#include "Red/ScriptBundle.hpp"

namespace Raw::CClass
{
constexpr auto CreateInstance = Core::RawFunc<
    /* addr = */ RED4ext::Detail::AddressHashes::CClass_CreateInstance,
    /* type = */ Red::IScriptable* (*)(Red::CClass*, uint32_t, bool)>();
}

// namespace Raw::CBaseStack
// {
// constexpr auto ResolveContext = Core::RawFunc<
//     /* addr = */ Red::AddressLib::CBaseStack_ResolveContext,
//     /* type = */ Red::IScriptable* (*)(Red::CBaseStack*)>();
// }

// namespace Raw::CBaseFunction
// {
// constexpr auto InternalExecute = Core::RawFunc<
//     /* addr = */ Red::AddressLib::CBaseFunction_InternalExecute,
//     /* type = */ bool (*)(Red::CBaseFunction*, Red::CBaseStack*, Red::CStackFrame*)>();
// }

namespace Raw::ScriptValidator
{
constexpr auto Validate = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptValidator_Validate,
    /* type = */ bool (*)(void* aValidator, Red::ScriptBundle* aBundle, void* aReport)>();

constexpr auto ValidateProperty = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptValidator_ValidateProperty,
    /* type = */ bool (*)(void* aValidator, Red::ScriptProperty* aScriptProp, Red::CProperty* aNativeProp)>();

constexpr auto CompareType = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptValidator_CompareType,
    /* type = */ bool (*)(Red::CBaseRTTIType* aNativeType, Red::ScriptType* aScriptType)>();

constexpr auto CompareTypeName = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptValidator_CompareTypeName,
    /* type = */ bool (*)(Red::CName aScriptTypeName, Red::CName aNativeTypeName)>();
}

namespace Raw::ScriptBundle
{
constexpr auto Destruct = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptBundle_dtor,
    /* type = */ void (*)(Red::ScriptBundle* aBundle)>();
}

namespace Raw::ScriptOpCodes
{
using Handler = void(*)(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType* aType);

constexpr uint8_t New = 48;
constexpr uint8_t Cast = 90;

constexpr auto Register = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptOpCodes_Register,
    /* type = */ void (*)()>();

constexpr auto Handlers = Core::RawPtr<
    /* addr = */ Red::AddressLib::ScriptOpCodes_Handlers,
    /* type = */ Handler>();

constexpr auto HandlerNew = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptOpCodes_Handlers_New,
    /* type = */ void (*)(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType* aType)>();

constexpr auto HandlerCast = Core::RawFunc<
    /* addr = */ Red::AddressLib::ScriptOpCodes_Handlers_Cast,
    /* type = */ void (*)(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType* aType)>();
}

namespace Raw::ISerializable
{
constexpr auto Clone = Core::RawFunc<
    /* addr = */ Red::AddressLib::ISerializable_Clone,
    /* type = */ void* (*)(Red::Handle<Red::ISerializable>& aOut,
                           const Red::Handle<Red::ISerializable>& aObject)>();
}

// namespace Raw::IScriptable
// {
// constexpr auto CheckClass = Core::RawFunc<
//     /* addr = */ Red::AddressLib::IScriptable_CheckClass,
//     /* type = */ void (*)(Red::IScriptable* aContext, Red::CStackFrame*, bool* aRet, Red::CBaseRTTIType*)>();
//
// constexpr auto CheckExactClass = Core::RawFunc<
//     /* addr = */ Red::AddressLib::IScriptable_CheckExactClass,
//     /* type = */ void (*)(Red::IScriptable* aContext, Red::CStackFrame*, bool* aRet, Red::CBaseRTTIType*)>();
// }
