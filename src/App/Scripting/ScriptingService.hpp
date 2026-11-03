#pragma once

#include "App/Scripting/ScriptableServiceContainer.hpp"
#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/GameFramework.hpp"
#include "Red/GameInstance.hpp"
#include "Red/Scripting.hpp"

namespace App
{
class ScriptingService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    ScriptingService(const std::filesystem::path& aStateDir);

protected:
    void OnBootstrap() override;

#if defined(__APPLE__)
    // macOS: the two lifecycle events (Support/macOS/Lifecycle.hpp) stand in for the ScriptBundle::Destruct hook.
    static void OnMacNativesRegistered();
    static void OnMacServicesStart(); // postLoadScripts fallback
    static void OnMacScriptBundleDestroyed();
    static void OnMacGameInstanceInitialized(void* aData, void* aParam);
    static void OnMacCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint64_t a2, bool a3);
    static void MacStartServices(const char* aVia);
#endif

    static void OnInitializeScripts();
    static void OnInitializeGameInstance();
    static void OnCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint64_t, bool);
    static void OnValidateScripts(void* aValidator, Red::ScriptBundle* aBundle, void* aReport);
    static bool OnValidateProperty(void* aValidator, Red::ScriptProperty* aScriptProp, Red::CProperty* aNativeProp);
    static bool OnValidateScriptType(Red::CBaseRTTIType* aNativeType, Red::ScriptType* aScriptType);
    static void OnValidateTypeName(bool& aValid, Red::CName aScriptTypeName, Red::CName aNativeTypeName);
    static void OnRegisterScriptOpCodes();
    static void ScriptOpCodeNew(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType*);
    static void ScriptOpCodeCast(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType*);
    static void GetScriptGameInstance(Red::IScriptable*, Red::CStackFrame* aFrame,
                                      Red::ScriptGameInstance* aRet, Red::CBaseRTTIType*);

    inline static std::filesystem::path s_stateDir;
};
}
