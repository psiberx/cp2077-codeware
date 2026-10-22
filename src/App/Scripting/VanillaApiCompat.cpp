#include "VanillaApiCompat.hpp"

namespace
{
// Codeware native type name (also its script name) -> the vanilla native type that game 2.5
// registers under the same script name (strings at 0x3626A18..0x3628400 in the 2.5 exe).
constexpr std::pair<Red::CName, Red::CName> SharedScriptNames[] = {
    {"CallbackSystem", "gameCallbackSystem"},
    {"CallbackSystemEvent", "gameCallbackSystemEvent"},
    {"CallbackSystemHandler", "gameCallbackSystemHandler"},
    {"CallbackSystemTarget", "gameCallbackSystemTarget"},
    {"GameSessionEvent", "gameGameSessionEvent"},
    {"ResourceEvent", "gameResourceEvent"},
    {"ResourceTarget", "gameResourceTarget"},
    {"InputTarget", "gameInputTarget"},
    {"KeyInputEvent", "gameKeyInputEvent"},
    {"ScriptableService", "gameScriptableService"},
    {"ScriptableServiceContainer", "gameScriptableServiceContainer"},
};

// GameInstance static getters that both the game and Codeware register. Codeware's return type is
// its own class; the vanilla one returns the vanilla class.
constexpr std::pair<Red::CName, Red::CName> SharedGetters[] = {
    {"GetCallbackSystem", "CallbackSystem"},
    {"GetScriptableServiceContainer", "ScriptableServiceContainer"},
};

constexpr auto VanillaMarkerType = Red::CName("gameCallbackSystem");

Red::CName GetReturnTypeName(Red::CBaseFunction* aFunc)
{
    if (!aFunc || !aFunc->returnType || !aFunc->returnType->type)
        return {};

    auto* type = aFunc->returnType->type;

    if (type->GetType() == Red::ERTTIType::Handle)
    {
        auto* inner = reinterpret_cast<Red::CRTTIHandleType*>(type)->innerType;
        return inner ? inner->GetName() : Red::CName{};
    }

    return type->GetName();
}
}

bool App::VanillaApiCompat::IsSharedScriptName(Red::CName aName)
{
    for (const auto& [codewareName, vanillaName] : SharedScriptNames)
    {
        if (codewareName == aName)
            return true;
    }
    return false;
}

void App::VanillaApiCompat::Apply()
{
    auto* rtti = Red::CRTTISystem::Get();

    if (!rtti || !rtti->GetClass(VanillaMarkerType))
        return;

    if (!s_scriptNamesApplied)
    {
        s_scriptNamesApplied = true;

        for (const auto& [codewareName, vanillaName] : SharedScriptNames)
        {
            auto* codewareType = rtti->GetClass(codewareName);
            auto* vanillaType = rtti->GetClass(vanillaName);

            if (!codewareType)
            {
                LogWarning("[VanillaApiCompat] {}: Codeware type not registered, script name left to {}.",
                           codewareName.ToString(), vanillaType ? vanillaName.ToString() : "nobody");
                continue;
            }

            rtti->RegisterScriptName(codewareName, codewareName);

            auto* bound = rtti->GetClassByScriptName(codewareName);
            LogInfo("[VanillaApiCompat] script name {} -> {} (vanilla {}: {}).", codewareName.ToString(),
                    bound ? bound->GetName().ToString() : "null", vanillaName.ToString(),
                    vanillaType ? "present" : "absent");
        }
    }

    if (!s_gettersApplied)
    {
        auto* gameType = Red::GetClass<Red::ScriptGameInstance>();

        if (!gameType)
            return;

        s_gettersApplied = true;

        for (const auto& [getterName, codewareType] : SharedGetters)
        {
            Red::CClassStaticFunction* codewareGetter = nullptr;
            std::vector<Red::CClassStaticFunction*> vanillaGetters;

            for (auto* func : gameType->staticFuncs)
            {
                if (!func || func->shortName != getterName)
                    continue;

                if (GetReturnTypeName(func) == codewareType)
                    codewareGetter = func;
                else
                    vanillaGetters.push_back(func);
            }

            if (!codewareGetter)
            {
                LogWarning("[VanillaApiCompat] GameInstance.{}: Codeware getter not found, {} vanilla left.",
                           getterName.ToString(), vanillaGetters.size());
                continue;
            }

            for (auto* func : vanillaGetters)
            {
                gameType->staticFuncs.Remove(func);
            }

            LogInfo("[VanillaApiCompat] GameInstance.{}: removed {} vanilla getter(s), Codeware's kept ({} param).",
                    getterName.ToString(), vanillaGetters.size(), codewareGetter->params.Size());
        }
    }
}
