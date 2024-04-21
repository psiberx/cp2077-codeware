#include "ScriptingService.hpp"
#include "ScriptableEnv.hpp"
#include "App/Depot/ResourceReference.hpp"

namespace
{
constexpr auto ISerializableTypeName = Red::GetTypeName<Red::ISerializable>();
constexpr auto IScriptableTypeName = Red::GetTypeName<Red::IScriptable>();

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

    if (!HookBefore<Raw::ScriptValidator::Validate>(&OnValidateScripts))
        throw std::runtime_error("Failed to hook ScriptValidator::Validate.");

    if (!Hook<Raw::ScriptValidator::CompareType>(&OnValidateScriptType))
        throw std::runtime_error("Failed to hook ScriptValidator::CompareType.");

    if (!HookAfter<Raw::ScriptValidator::CompareTypeName>(&OnValidateTypeName))
        throw std::runtime_error("Failed to hook ScriptValidator::CompareTypeName.");

    if (!HookAfter<Raw::ScriptOpCodes::Register>(&OnRegisterScriptOpCodes))
        throw std::runtime_error("Failed to hook ScriptOpCodes::Register.");

    if (!HookAfter<Raw::CClass::CreateInstance>(&OnCreateInstance))
        throw std::runtime_error("Failed to hook CClass::CreateInstance.");

    if (!Hook<Raw::IScriptable::CheckClass>(&OnCheckScriptableClass))
        throw std::runtime_error("Failed to hook IScriptable::CheckClass.");

    if (!Hook<Raw::IScriptable::CheckExactClass>(&OnCheckScriptableExactClass))
        throw std::runtime_error("Failed to hook IScriptable::CheckExactClass.");

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
            if (envType->flags.isAbstract)
            {
                LogWarning("Can't create scriptable environment {} because class is abstract.",
                           envType->name.ToString());
                continue;
            }

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

void App::ScriptingService::OnValidateScripts(void* aValidator, Red::ScriptBundle* aBundle, void* aReport)
{
    for (auto& classDef : aBundle->classes)
    {
        if (classDef->flags.isNative)
        {
            if (classDef->name == ISerializableTypeName)
            {
                classDef->flags.isStruct = true;
                classDef->parent = nullptr;
            }
            else if (!classDef->flags.isStruct)
            {
                auto parent = classDef->parent;
                while (parent)
                {
                    if (parent->name == IScriptableTypeName)
                    {
                        break;
                    }
                    if (parent->name == ISerializableTypeName)
                    {
                        classDef->flags.isStruct = true;
                        break;
                    }
                    parent = parent->parent;
                }
            }

            if (classDef->flags.isStruct)
            {
                if (auto nativeClass = Red::GetScriptClass(classDef->name))
                {
                    classDef->flags.isAbstract = nativeClass->flags.isAbstract;
                }
            }
        }
    }
}

bool App::ScriptingService::OnValidateScriptType(Red::CBaseRTTIType* aNativeType, Red::ScriptType* aScriptType)
{
    if (aScriptType->metaType == Red::EScriptType::DynArray)
    {
        if (aNativeType->GetType() == Red::ERTTIType::Array)
        {
            auto nativeInnerType = reinterpret_cast<Red::CRTTIBaseArrayType*>(aNativeType)->innerType;
            auto scriptInnerType = reinterpret_cast<Red::ScriptType*>(aScriptType->innerType);

            return OnValidateScriptType(nativeInnerType, scriptInnerType);
        }
        return false;
    }

    return Raw::ScriptValidator::CompareType(aNativeType, aScriptType);
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

void App::ScriptingService::OnRegisterScriptOpCodes()
{
    Raw::ScriptOpCodes::Handlers[Raw::ScriptOpCodes::New] = &ScriptOpCodeNew;
    Raw::ScriptOpCodes::Handlers[Raw::ScriptOpCodes::Cast] = &ScriptOpCodeCast;
}

void App::ScriptingService::ScriptOpCodeNew(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet,
                                            Red::CBaseRTTIType*)
{
    auto instanceType = *reinterpret_cast<Red::CClass**>(aFrame->code);
    aFrame->code += sizeof(Red::CClass*);

    if (aRet)
    {
        *reinterpret_cast<Red::Handle<Red::ISerializable>*>(aRet) = Red::MakeScriptedHandle(instanceType);
    }
}

void App::ScriptingService::ScriptOpCodeCast(Red::IScriptable*, Red::CStackFrame* aFrame, void* aLhs,
                                             Red::CBaseRTTIType*)
{
    auto lhsType = *reinterpret_cast<Red::CClass**>(aFrame->code);
    aFrame->code += sizeof(Red::CClass*);

    auto isWeak = *reinterpret_cast<bool*>(aFrame->code);
    aFrame->code += sizeof(bool);

    if (isWeak)
    {
        Red::WeakHandle<Red::ISerializable> rhsWeak;
        Red::GetParameter(aFrame, &rhsWeak);

        if (aLhs)
        {
            auto rhs = rhsWeak.Lock();
            if (rhs && !rhs->GetType()->IsA(lhsType))
            {
                rhs.Reset();
            }

            *reinterpret_cast<Red::WeakHandle<Red::ISerializable>*>(aLhs) = rhs;
        }
    }
    else
    {
        Red::Handle<Red::ISerializable> rhs;
        Red::GetParameter(aFrame, &rhs);

        if (aLhs)
        {
            if (rhs && !rhs->GetType()->IsA(lhsType))
            {
                rhs.Reset();
            }

            *reinterpret_cast<Red::Handle<Red::ISerializable>*>(aLhs) = rhs;
        }
    }
}

void App::ScriptingService::OnCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint32_t, bool)
{
    if (aInstance && aClass->flags.isScriptedClass)
    {
        Red::CallVirtual(aInstance, aClass, "OnConstruct");
    }
}

void App::ScriptingService::OnCheckScriptableClass(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                                   bool* aRet, Red::CBaseRTTIType* aType)
{
    if (aContext && !aContext->GetNativeType()->IsA(Red::GetClass<Red::IScriptable>()))
    {
        Red::CName className;
        Red::GetParameter(aFrame, &className);
        ++aFrame->code;

        if (aRet)
        {
            *aRet = aContext->GetNativeType()->IsA(Red::GetClass(className));
        }
    }
    else
    {
        Raw::IScriptable::CheckClass(aContext, aFrame, aRet, aType);
    }
}

void App::ScriptingService::OnCheckScriptableExactClass(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
                                                        bool* aRet, Red::CBaseRTTIType* aType)
{
    if (aContext && !aContext->GetNativeType()->IsA(Red::GetClass<Red::IScriptable>()))
    {
        Red::CName className;
        Red::GetParameter(aFrame, &className);
        ++aFrame->code;

        if (aRet)
        {
            *aRet = (aContext->GetNativeType()->name == className);
        }
    }
    else
    {
        Raw::IScriptable::CheckExactClass(aContext, aFrame, aRet, aType);
    }
}

void App::ScriptingService::GetScriptGameInstance(Red::IScriptable*, Red::CStackFrame* aFrame,
                                                  Red::ScriptGameInstance* aRet, Red::CBaseRTTIType*)
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
