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

// Game 2.5 also registers native ResRef.ToString / ResRef.GetHash (static functions of
// redResourceReferenceScriptToken; the 2.5 bundle declares them in its `ResRef` struct). The script call
// binds to the first function of that name, the vanilla one, and its ToString answers "" for paths the
// game keeps no string for (every mesh path on a live V, 2.5 game lane G-NEW-game-5). Codeware's own
// (ResourcePathRegistry) is kept, the vanilla ones are removed. The live 2.5 RTTI (funcs.jsonl:52256-52259)
// lists the vanilla pair first (parameter `path`) and Codeware's expansion after it (parameter `arg`):
// with two of a name, the last registered is Codeware's.
void App::VanillaApiCompat::ApplyResRefNatives()
{
    auto* type = Red::CRTTISystem::Get()->GetClass("redResourceReferenceScriptToken");
    if (!type)
    {
        LogWarning("[VanillaApiCompat] ResRef: redResourceReferenceScriptToken not registered.");
        s_resRefApplied = true;
        return;
    }

    constexpr Red::CName Names[] = {"ToString", "GetHash"};
    for (auto name : Names)
    {
        std::vector<Red::CClassStaticFunction*> found;
        for (auto* func : type->staticFuncs)
            if (func && func->shortName == name)
                found.push_back(func);

        if (found.size() < 2)
        {
            if (name == Names[0])
                return; // Codeware's expansion not registered yet (or no vanilla one): next Apply decides
            continue;
        }

        auto paramName = [](Red::CClassStaticFunction* aFunc) {
            return aFunc->params.Size() > 0 && aFunc->params[0] ? std::string(aFunc->params[0]->name.ToString()) : std::string("-");
        };
        auto* kept = found.back();
        std::string removed;
        for (size_t i = 0; i + 1 < found.size(); ++i)
        {
            removed += std::string(removed.empty() ? "" : ",") + paramName(found[i]);
            type->staticFuncs.Remove(found[i]);
        }
        s_resRefApplied = true;
        LogInfo("[VanillaApiCompat] ResRef.{}: removed {} earlier native(s) (param {}), kept the last (param {}).",
                name.ToString(), found.size() - 1, removed, paramName(kept));
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

    if (!s_resRefApplied)
    {
        ApplyResRefNatives();
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
