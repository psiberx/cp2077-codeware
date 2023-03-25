#include "ScriptingService.hpp"
#include "ResourceWrapper.hpp"

namespace
{
constexpr auto ResourceWrapperName = Red::GetTypeName<App::ResourceWrapper>();
constexpr auto ResourceAsyncWrapperName = Red::GetTypeName<App::ResourceAsyncWrapper>();
constexpr auto ScriptResourceReferenceAlias = Red::CName(Red::redResourceReferenceScriptToken::ALIAS);

constexpr auto ResourceReferencePrefix = Red::GetTypePrefixStr<Red::ResourceReference>();
constexpr auto ResourceAsyncReferencePrefix = Red::GetTypePrefixStr<Red::ResourceAsyncReference>();
}

void App::ScriptingService::OnBootstrap()
{
    if (!HookAfter<Raw::IScriptable::InitializeScriptData>(&OnInitializeScriptable))
        throw std::runtime_error("Failed to hook IScriptable::InitializeScriptData.");

    if (!HookAfter<Raw::ScriptValidator::CompareTypeName>(&OnValidateTypeName))
        throw std::runtime_error("Failed to hook ScriptValidator::CompareTypeName.");
}

void App::ScriptingService::OnInitializeScriptable(Red::IScriptable* aInstance, Red::CClass* aClass, void*)
{
    if (aClass->flags.isScriptedClass)
    {
        Red::CallVirtual(aInstance, aClass, "OnConstruct");
    }
}

void App::ScriptingService::OnValidateTypeName(bool& aValid, Red::CName aScriptTypeName, Red::CName aNativeTypeName)
{
    if (!aValid)
    {
        if (aScriptTypeName == ResourceWrapperName)
        {
            aValid = strncmp(ResourceReferencePrefix.data(), aNativeTypeName.ToString(),
                             ResourceReferencePrefix.size() - 1) == 0;
        }
        else if (aScriptTypeName == ResourceAsyncWrapperName || aScriptTypeName == ScriptResourceReferenceAlias)
        {
            aValid = strncmp(ResourceAsyncReferencePrefix.data(), aNativeTypeName.ToString(),
                             ResourceAsyncReferencePrefix.size() - 1) == 0;
        }
    }
}
