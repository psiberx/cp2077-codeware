#include "ScriptingService.hpp"
#include "ResourceWrapper.hpp"

namespace
{
constexpr auto ResourceWrapperName = Red::GetTypeName<App::ResourceWrapper>();
constexpr auto ResourceAsyncWrapperName = Red::GetTypeName<App::ResourceAsyncWrapper>();

constexpr auto ResourceReferencePrefix = Red::GetTypeNamePrefix<Red::ResourceReference<>>();
constexpr auto ResourceAsyncReferencePrefix = Red::GetTypeNamePrefix<Red::ResourceAsyncReference<>>();

constexpr auto ScriptResourceReferenceName = Red::CName(Red::ResRef::ALIAS);
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
        else if (aScriptTypeName == ResourceAsyncWrapperName || aScriptTypeName == ScriptResourceReferenceName)
        {
            aValid = strncmp(ResourceAsyncReferencePrefix.data(), aNativeTypeName.ToString(),
                             ResourceAsyncReferencePrefix.size() - 1) == 0;
        }
    }
}
