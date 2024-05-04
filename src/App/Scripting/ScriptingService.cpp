#include "ScriptingService.hpp"
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

constexpr auto KnowNameConflict = Red::CName("inkWidgetLibraryResource");
}

App::ScriptingService::ScriptingService(const std::filesystem::path& aStateDir)
{
    s_stateDir = aStateDir;
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

    if (!Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance))
        throw std::runtime_error("Failed to hook ScriptGameInstance.");
}

void App::ScriptingService::OnInitializeScripts()
{
    if (Red::Detail::GetGlobalFunction("InitializeScripts;"))
    {
        if (!Red::CGameEngine::Get()->scriptsLoaded)
        {
            ScriptableServiceContainer::Build(s_stateDir)->OnInitializeScripts();
        }
        else
        {
            ScriptableServiceContainer::Get()->OnInitializeScripts();
        }
    }
}

void App::ScriptingService::OnInitializeGameInstance()
{
    ScriptableServiceContainer::Get()->OnInitializeGameInstance();
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
                auto parentDef = classDef->parent;
                while (parentDef)
                {
                    if (parentDef->name == IScriptableTypeName)
                    {
                        break;
                    }
                    if (parentDef->name == ISerializableTypeName)
                    {
                        classDef->flags.isStruct = true;
                        break;
                    }
                    parentDef = parentDef->parent;
                }
            }

            if (classDef->flags.isStruct && classDef->name != KnowNameConflict)
            {
                if (auto nativeClass = Red::GetScriptClass(classDef->name))
                {
                    classDef->flags.isAbstract = nativeClass->flags.isAbstract;

                    if (!classDef->parent && nativeClass->parent)
                    {
                        auto nativeParent = nativeClass->parent;
                        auto parentDef = aBundle->definitionsByName.Get(nativeParent->name);

                        if (!parentDef)
                        {
                            if (auto parentAlias = Red::GetScriptAlias(nativeParent->name))
                            {
                                parentDef = aBundle->definitionsByName.Get(parentAlias);
                            }
                        }

                        classDef->parent = reinterpret_cast<Red::ScriptClass*>(*parentDef);

                        if (classDef->properties.size > 0)
                        {
                            while (nativeParent)
                            {
                                for (auto i = static_cast<int32_t>(classDef->properties.size) - 1; i >= 0; --i)
                                {
                                    if (nativeParent->GetProperty(classDef->properties[i]->name))
                                    {
                                        classDef->properties.RemoveAt(i);
                                    }
                                }
                                nativeParent = nativeParent->parent;
                            }
                        }
                    }
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
