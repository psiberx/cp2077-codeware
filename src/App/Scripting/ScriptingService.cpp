#include "ScriptingService.hpp"
#include "ScriptableEnv.hpp"
#include "App/Depot/ResourceReference.hpp"

namespace
{
constexpr auto ResourceWrapperName = Red::GetTypeName<App::ResourceWrapper>();
constexpr auto ResourceAsyncWrapperName = Red::GetTypeName<App::ResourceAsyncWrapper>();
constexpr auto ResourceScriptReferenceAlias = Red::CName(Red::redResourceReferenceScriptToken::ALIAS);
constexpr auto ResourceReferencePrefix = Red::GetTypePrefixStr<Red::ResourceReference>();
constexpr auto ResourceAsyncReferencePrefix = Red::GetTypePrefixStr<Red::ResourceAsyncReference>();
}

void App::ScriptingService::OnBootstrap()
{
    if (!HookAfter<Raw::ScriptBundle::Destruct>(&OnInitializeScripts))
        throw std::runtime_error("Failed to hook ScriptBundle::Destruct.");

    if (!HookAfter<Raw::CGameFramework::InitializeGameInstance>(&OnInitializeGameInstance))
        throw std::runtime_error("Failed to hook CGameFramework::InitializeGameInstance.");

    if (!HookAfter<Raw::IScriptable::InitializeScriptData>(&OnInitializeInstance))
        throw std::runtime_error("Failed to hook IScriptable::InitializeScriptData.");

    if (!HookAfter<Raw::ScriptValidator::CompareTypeName>(&OnValidateTypeName))
        throw std::runtime_error("Failed to hook ScriptValidator::CompareTypeName.");

    if (!Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance))
        throw std::runtime_error("Failed to hook ScriptGameInstance.");
}

void App::ScriptingService::OnInitializeScripts()
{
    Red::DynArray<Red::CClass*> envTypes;
    Red::CRTTISystem::Get()->GetDerivedClasses(Red::GetClass<ScriptableEnv>(), envTypes);

    for (auto envType : envTypes)
    {
        const auto& envIt = s_environments.find(envType);

        if (envIt != s_environments.end())
        {
            auto& env = envIt.value();
            Red::CallVirtual(env, "OnReload");
        }
        else
        {
            auto env = Red::ToHandle<ScriptableEnv>(envType->CreateInstance());
            Red::CallVirtual(env, "OnLoad");

            s_environments.emplace(envType, std::move(env));
        }
    }
}

void App::ScriptingService::OnInitializeGameInstance()
{
    for (const auto& [envType, env] : s_environments)
    {
        Red::CallVirtual(env, "OnInitialize");
    }
}

void App::ScriptingService::OnInitializeInstance(Red::IScriptable* aInstance, Red::CClass* aClass, void*)
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
        else if (aScriptTypeName == ResourceAsyncWrapperName || aScriptTypeName == ResourceScriptReferenceAlias)
        {
            aValid = strncmp(ResourceAsyncReferencePrefix.data(), aNativeTypeName.ToString(),
                             ResourceAsyncReferencePrefix.size() - 1) == 0;
        }
    }
}

void App::ScriptingService::GetScriptGameInstance(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                                  Red::ScriptGameInstance* aRet, Red::CBaseRTTIType* aType)
{
    static const Red::ScriptGameInstance game{};

    ++aFrame->code;

    if (aRet)
    {
        *aRet = game;
    }
}

Red::Handle<App::ScriptableEnv> App::ScriptingService::GetEnvironment(Red::CClass* aType)
{
    auto it = s_environments.find(aType);

    if (it == s_environments.end())
        return {};

    return it.value();
}
