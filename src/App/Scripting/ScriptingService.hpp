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

    static void OnInitializeScripts();
    static void OnInitializeGameInstance();
    static void OnCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint32_t, bool);
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
