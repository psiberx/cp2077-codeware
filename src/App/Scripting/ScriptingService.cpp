#include "ScriptingService.hpp"
#include "App/Depot/ResourceReference.hpp"
#include "App/Engine/CurveData.hpp"
#include "App/Scripting/VanillaApiCompat.hpp"

#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "Red/Serialization.hpp"
#include "MacR19.hpp"
#include "MacR13.hpp"
#include "MacR15.hpp"
#include "Support/macOS/Lifecycle.hpp"
#include "App/Callback/MacHookStats.hpp"

#include <atomic>
#include <cstdlib>
#include <cstring>
#include "MacDiag.hpp"

namespace
{
std::atomic<bool> s_servicesStarted{false};
}
#endif

namespace
{
constexpr auto ISerializableTypeName = Red::GetTypeName<Red::ISerializable>();
constexpr auto IScriptableTypeName = Red::GetTypeName<Red::IScriptable>();

constexpr auto ResourceWrapperName = Red::GetTypeName<App::ResourceWrapper>();
constexpr auto ResourceAsyncWrapperName = Red::GetTypeName<App::ResourceAsyncWrapper>();
constexpr auto ResourceScriptReferenceAlias = Red::CName(Red::redResourceReferenceScriptToken::ALIAS);
constexpr auto ResourceReferencePrefix = Red::GetTypePrefixStr<Red::ResourceReference>();
constexpr auto ResourceAsyncReferencePrefix = Red::GetTypePrefixStr<Red::ResourceAsyncReference>();

constexpr auto CurveDataWrapperFloatName = Red::GetTypeName<App::CurveDataWrapper<float>>();
constexpr auto CurveDataWrapperVector2Name = Red::GetTypeName<App::CurveDataWrapper<Red::Vector2>>();
constexpr auto CurveDataWrapperVector3Name = Red::GetTypeName<App::CurveDataWrapper<Red::Vector3>>();
constexpr auto CurveDataWrapperVector4Name = Red::GetTypeName<App::CurveDataWrapper<Red::Vector4>>();
constexpr auto CurveDataWrapperHDRColorName = Red::GetTypeName<App::CurveDataWrapper<Red::HDRColor>>();
constexpr auto CurveDataPrefix = Red::GetTypePrefixStr<Red::CurveData>();

constexpr auto inkWidgetLibraryResourceTypeName = Red::CName("inkWidgetLibraryResource");
constexpr auto gameuiBaseUIDataTypeName = Red::CName("gameuiBaseUIData");
constexpr auto scnChatterTypeName = Red::CName("scnChatter");
constexpr auto audioEventElementTypeName = Red::CName("audioAudioEventMetadataArrayElement");
constexpr auto entLODDefinitionTypeName = Red::CName("entLODDefinition");

constexpr auto GameCallbackRunModeName = Red::CName("gameCallbackRunMode");
constexpr auto GameCallbackLifetimeName = Red::CName("gameCallbackLifetime");
constexpr auto CallbackRunModeName = Red::CName("CallbackRunMode");
constexpr auto CallbackLifetimeName = Red::CName("CallbackLifetime");
}

App::ScriptingService::ScriptingService(const std::filesystem::path& aStateDir)
{
    s_stateDir = aStateDir;

    // R19: the state directory (red4ext/plugins/Codeware/Persistent) is created on macOS too; SaveState writes there.
    // Queued after every RTTI_DEFINE_CLASS registrar (static init), so Codeware's system getters exist.
    Red::TypeInfoRegistrar::AddDescribeCallback(&VanillaApiCompat::Apply);

    std::error_code error;
    if (!std::filesystem::exists(s_stateDir, error))
    {
        if (!std::filesystem::create_directories(s_stateDir, error))
        {
            LogError("Cannot create directory \"{}\" for persistent data: {}.", s_stateDir.string(), error.message());
        }
    }
}

#if defined(__APPLE__)
void App::ScriptingService::OnBootstrap()
{
    // The Windows hooks, one by one, and what takes their place on macOS:
    //   HookAfter<ScriptBundle::Destruct>(OnInitializeScripts)          -> the two lifecycle events below
    //   HookAfter<CGameFramework::InitializeGameInstance>               -> Red::MacInstallGameInstanceHook (GameInstance
    //                                                                       constructor; the world attach runs OnInitialize)
    //   HookBefore<ScriptValidator::Validate>, Hook<ValidateProperty>,
    //   HookAfter<CompareTypeName>, HookAfter<ScriptOpCodes::Register>  -> Mac::InstallScriptValidatorHooks and
    //                                                                       Mac::PatchScriptOpCodes (macos/MacScriptValidator.cpp:
    //                                                                       a port with the Mac ABI and layout checks;
    //                                                                       CompareTypeName is inlined on Mac)
    //   Hook<GetScriptGameInstance>                                     -> Mac::InstallGetGameInstanceHook (the Mac native
    //                                                                       returns the live instance)
    //   HookAfter<CClass::CreateInstance>(OnCreateInstance)             -> OnMacCreateInstance (R19), the same OnCreateInstance
    // MAC-NOT-YET: ScriptValidator_CompareTypeName is not applicable on Mac (the game inlines the comparison into ScriptValidator::Validate, so there is no function to map or hook; the documented plain call to CompareType stands in, R15).
    // R18: HookAfter<ScriptBundle::Destruct> and HookAfter<CGameFramework::InitializeGameInstance> are installed for real
    // (ScriptBundle destructor 0x21ECFD8, the framework's GameInstance job body 0x3F0D900). The lifecycle events and the first
    // world attach stay as the fallback when a hook is refused; the log says which path ran.
    const bool instanceOk = Red::MacInstallGameInstanceHook();
    const bool giOk = Mac::InstallGetGameInstanceHook();
    const bool validatorOk = Mac::InstallScriptValidatorHooks();
    LogInfo("ScriptingService hooks: gameInstance={} getGameInstance={} validator={}", instanceOk, giOk, validatorOk);
    Mac::PatchScriptOpCodes("load");

    // R18 B0. Engine timing and the singletons: InitEngine (captures CGameEngine) and LoadGatheredResources.
    const bool engineOk = Mac::InstallEngineHooks();
    // The services start when the validated script bundle is destroyed, like on Windows; OnInitializeGameInstance runs
    // after the framework's GameInstance job.
    const bool dtorOk = HookAfter<Raw::ScriptBundle::Destruct>(&OnMacScriptBundleDestroyed);
    const bool initOk = Hook<Raw::CGameFramework::InitializeGameInstance>(&OnMacGameInstanceInitialized);
    LogInfo("ScriptingService timing hooks: engine={} scriptBundleDtor={} initializeGameInstance={}", engineOk, dtorOk, initOk);

    // R19 B2. The serializer's Prepare hook for the magic size limit, installed now so SaveState never patches at run time.
    const bool prepareOk = Red::ObjectSerializer::InstallPrepareHook();
    MAC_DIAG_UNLESS(prepareOk, "[cw] hook %s ObjectSerializer::Prepare target=%p\n", prepareOk ? "installed" : "FAILED",
                 reinterpret_cast<void*>(Raw::ObjectSerializer::Prepare.GetOriginalAddress()));

    // R19 B2. Scripted classes get their OnConstruct call after CClass::CreateInstance, like on Windows (on by default;
    // CODEWARE_MAC_ONCONSTRUCT=0 turns it off). Mac needs a Handle held around the
    // call, see MacRefReleaser below.
    static const bool s_onConstruct = Mac::R19OnConstructMode() != 0;
    if (s_onConstruct)
    {
        const bool createOk = HookAfter<Raw::CClass::CreateInstance>(&OnMacCreateInstance);
        MAC_DIAG_UNLESS(createOk, "[cw] hook %s ScriptingService CClass::CreateInstance target=%p\n", createOk ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::CClass::CreateInstance.GetOriginalAddress()));
    }
    else
    {
        std::fprintf(stderr, "[cw] CClass::CreateInstance hook off (OnConstruct dispatch, CODEWARE_MAC_ONCONSTRUCT=0)\n");
    }

    Mac::Lifecycle::OnNativesRegistered(&OnMacNativesRegistered, "ScriptingService");
    Mac::Lifecycle::OnServicesStart(&OnMacServicesStart, "ScriptingService");
}

void App::ScriptingService::OnMacNativesRegistered()
{
    // The container exists before the scripts are linked, so the scripted services (ScriptableService subclasses) can
    // be created once the scripts are loaded.
    ScriptableServiceContainer::Build(s_stateDir);
}

void App::ScriptingService::MacStartServices(const char* aVia)
{
    if (s_servicesStarted.exchange(true))
    {
        return;
    }

    MAC_DIAG("[cw] services start via %s t=%lldms\n", aVia,
                 static_cast<long long>(App::MacHookStats::SinceLoadMs()));

    auto& container = ScriptableServiceContainer::Get();
    if (container)
    {
        container->OnInitializeScripts();
    }
    else
    {
        LogError("ScriptableServiceContainer does not exist, the services are not started.");
    }
}

void App::ScriptingService::OnMacServicesStart()
{
    // The postLoadScripts path: the fallback when the ScriptBundle destructor hook was refused or did not fire.
    MacStartServices("postLoadScripts (fallback, the ScriptBundle destructor hook did not start them)");
}

void App::ScriptingService::OnMacScriptBundleDestroyed()
{
    static auto& counter = Mac::HookCount("ScriptBundle_dtor");
    Mac::Hit(counter);

    if (!Mac::ScriptsValidated() || s_servicesStarted.load())
    {
        return; // a bundle that was never validated (not the game's script bundle), or the services already run
    }

    Mac::PatchScriptOpCodes("scriptBundleDtor"); // the New and Cast handlers first: the services' OnLoad runs scripts
    MacStartServices("ScriptBundle destructor hook");
}

void App::ScriptingService::OnMacCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint64_t a2, bool a3)
{
    static auto& counter = Mac::HookCount("CClass_CreateInstance");
    Mac::Hit(counter);

    if (aInstance && aClass && aClass->flags.isScriptedClass)
    {
        static auto& scripted = Mac::HookCount("CClass_CreateInstance_scripted");
        Mac::Hit(scripted);
    }

    OnCreateInstance(aInstance, aClass, a2, a3);
}

void App::ScriptingService::OnMacGameInstanceInitialized(void* aData, void* aParam)
{
    static auto& counter = Mac::HookCount("CGameFramework_InitializeGameInstance");
    Mac::Hit(counter);

    // The job frees its closure when it returns, so the framework is read first. This is a full hook (the original runs
    // below) because a HookAfter would see the freed closure.
    Mac::OnFrameworkJob(aData);
    Raw::CGameFramework::InitializeGameInstance(aData, aParam);

    auto& container = ScriptableServiceContainer::Get();
    if (container)
    {
        container->MacInitializeGameInstance("CGameFramework::InitializeGameInstance hook");
    }
}
#else
void App::ScriptingService::OnBootstrap()
{
    HookAfter<Raw::ScriptBundle::Destruct>(&OnInitializeScripts).OrThrow();
    HookAfter<Raw::CGameFramework::InitializeGameInstance>(&OnInitializeGameInstance).OrThrow();
    HookBefore<Raw::ScriptValidator::Validate>(&OnValidateScripts).OrThrow();
    Hook<Raw::ScriptValidator::ValidateProperty>(&OnValidateProperty).OrThrow();
    HookAfter<Raw::ScriptValidator::CompareTypeName>(&OnValidateTypeName).OrThrow();
    HookAfter<Raw::ScriptOpCodes::Register>(&OnRegisterScriptOpCodes).OrThrow();
    HookAfter<Raw::CClass::CreateInstance>(&OnCreateInstance).OrThrow();
    Hook<Raw::GetScriptGameInstance>(&GetScriptGameInstance).OrThrow();
}
#endif

void App::ScriptingService::OnInitializeScripts()
{
    if (Red::GetGlobalFunction("InitializeScripts;"))
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
    VanillaApiCompat::Apply();

    Red::GetClass<gameuiBaseUIDataTypeName>()->parent = Red::GetClass<ISerializableTypeName>();
    Red::GetClass<scnChatterTypeName>()->parent = Red::GetClass<ISerializableTypeName>();

    for (auto& classDef : aBundle->classes)
    {
        if (classDef->flags.isNative)
        {
            // Game 2.5: the vanilla bundle declares ScriptableService / CallbackSystemEvent without
            // `abstract`, but their script names now resolve to Codeware's abstract types
            // (VanillaApiCompat), so the validator refuses "Native class '...' was not marked as abstract".
            if (VanillaApiCompat::IsSharedScriptName(classDef->name))
            {
                if (auto nativeClass = Red::GetScriptClass(classDef->name))
                {
                    classDef->flags.isAbstract = nativeClass->flags.isAbstract;
                }
            }

            if (classDef->name == ISerializableTypeName)
            {
                classDef->flags.isStruct = true;
                classDef->parent = nullptr;
            }
            else if (classDef->name == audioEventElementTypeName || classDef->name == entLODDefinitionTypeName)
            {
                classDef->flags.isStruct = true;
                classDef->parent = reinterpret_cast<Red::ScriptClass*>(*aBundle->definitionsByName.Get(ISerializableTypeName));
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

            if (auto nativeClass = Red::GetScriptClass(classDef->name))
            {
                classDef->flags.isAbstract = nativeClass->flags.isAbstract;

                if (classDef->flags.isStruct && !classDef->parent && nativeClass->parent &&
                    classDef->name != inkWidgetLibraryResourceTypeName)
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
                }
            }
        }
    }
}

bool App::ScriptingService::OnValidateProperty(void* aValidator, Red::ScriptProperty* aScriptProp,
                                               Red::CProperty* aNativeProp)
{
    auto* scriptType = aScriptProp->type;
    auto* nativeType = aNativeProp->type;

    if (scriptType->metaType == Red::EScriptType::DynArray ||
        scriptType->metaType == Red::EScriptType::StaticArray)
    {
        return OnValidateScriptType(nativeType, scriptType);
    }

    if (nativeType->GetType() == Red::ERTTIType::BitField && scriptType->metaType == Red::EScriptType::Primitive)
    {
        return true;
    }

    return Raw::ScriptValidator::ValidateProperty(aValidator, aScriptProp, aNativeProp);
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

    if (aScriptType->metaType == Red::EScriptType::StaticArray)
    {
        if (aNativeType->GetType() == Red::ERTTIType::StaticArray ||
            aNativeType->GetType() == Red::ERTTIType::NativeArray ||
            aNativeType->GetType() == Red::ERTTIType::FixedArray)
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
        // Game 2.5 declares CallbackSystemHandler.SetRunMode/SetLifetime with its own enums
        // (gameCallbackRunMode/gameCallbackLifetime, same members and values as Codeware's).
        if ((aScriptTypeName == GameCallbackRunModeName && aNativeTypeName == CallbackRunModeName) ||
            (aScriptTypeName == GameCallbackLifetimeName && aNativeTypeName == CallbackLifetimeName))
        {
            aValid = true;
            return;
        }

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
        else if (aScriptTypeName == CurveDataWrapperFloatName || aScriptTypeName == CurveDataWrapperVector2Name ||
                 aScriptTypeName == CurveDataWrapperVector3Name || aScriptTypeName == CurveDataWrapperVector4Name ||
                 aScriptTypeName == CurveDataWrapperHDRColorName)
        {
            aValid = strncmp(CurveDataPrefix.data(), aNativeTypeName.ToString(), CurveDataPrefix.size() - 1) == 0;
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

#if defined(__APPLE__)
namespace
{
// R19. On Mac the script VM ignores writes through `this` while the object has no handle yet (r19f: the same OnConstruct call
// sets the field when a Handle is held around it, and not otherwise). The hook therefore holds a temporary Handle for the
// call and gives its strong reference back afterwards WITHOUT destroying the object, which is what the caller expects: the
// object leaves CreateInstance with no owner, exactly as before. Handle's destructor would destroy it.
//
// The Handle constructor (Mac 0x2104788) registers the object's own weak reference to a new RefCnt {strong 1, weak 1}. DecRef
// below is the first half of ~Handle: strong 1 -> 0, then the strong references' collective weak reference is released. The
// object keeps its own weak reference to a RefCnt {strong 0, weak 1}. The caller's later Handle(ptr) sees strong 0 (the helper
// 0x2186638 only locks a ref whose strong count is above zero), creates a new RefCnt and swaps it in, which releases the old
// one; an object that never gets a handle releases it in its destructor. If the script kept a reference (strong above 0
// after the call) the object stays alive for its owners.
struct MacRefReleaser : Red::SharedPtrBase<Red::IScriptable>
{
    static void Release(Red::Handle<Red::IScriptable>& aHandle)
    {
        auto& base = reinterpret_cast<MacRefReleaser&>(aHandle);
        static_cast<void>(base.DecRef());
        base.instance = nullptr;
        base.refCount = nullptr;
    }
};
}
#endif

void App::ScriptingService::OnCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint64_t, bool)
{
    if (aInstance && aClass->flags.isScriptedClass)
    {
#if defined(__APPLE__)
        if (auto* function = Red::GetMemberFunction(aClass, "OnConstruct"))
        {
            Red::Handle<Red::IScriptable> hold(aInstance);
            Red::CallFunction(aInstance, function);
            MacRefReleaser::Release(hold);
        }
#else
        Red::CallVirtual(aInstance, aClass, "OnConstruct");
#endif
    }
}

void App::ScriptingService::GetScriptGameInstance(Red::IScriptable*, Red::CStackFrame* aFrame,
                                                  Red::ScriptGameInstance* aRet, Red::CBaseRTTIType*)
{
    ++aFrame->code;

    if (aRet)
    {
        *aRet = Red::ScriptGameInstance{};
    }
}
