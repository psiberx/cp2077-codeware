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
// (ResourcePathRegistry) is kept, the vanilla ones are removed. A function is Codeware's when its native
// handler (the global handler table, SDK CBaseFunction_Handlers, indexed by regIndex) lies in this module.
void App::VanillaApiCompat::ApplyResRefNatives()
{
    auto* type = Red::CRTTISystem::Get()->GetClass("redResourceReferenceScriptToken");
    if (!type)
        return;

    HMODULE self = nullptr;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                            reinterpret_cast<LPCWSTR>(&VanillaApiCompat::ApplyResRefNatives), &self))
        return;

    static RED4ext::UniversalRelocPtr<void*> handlers(RED4ext::Detail::AddressHashes::CBaseFunction_Handlers);

    constexpr Red::CName Names[] = {"ToString", "GetHash"};
    uint32_t codewareCount = 0;
    for (auto* func : type->staticFuncs)
    {
        if (func && func->flags.isNative)
            for (auto name : Names)
                if (func->shortName == name)
                {
                    HMODULE owner = nullptr;
                    auto handler = handlers.GetAddr()[func->regIndex];
                    if (handler &&
                        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                           reinterpret_cast<LPCWSTR>(handler), &owner) &&
                        owner == self)
                        ++codewareCount;
                }
    }
    if (codewareCount == 0)
        return; // Codeware's expansion not registered yet: try again on the next Apply

    s_resRefApplied = true;
    for (auto name : Names)
    {
        std::vector<Red::CClassStaticFunction*> vanilla;
        bool haveCodeware = false;
        for (auto* func : type->staticFuncs)
        {
            if (!func || func->shortName != name)
                continue;
            HMODULE owner = nullptr;
            auto handler = func->flags.isNative ? handlers.GetAddr()[func->regIndex] : nullptr;
            const bool mine = handler &&
                              GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                                     GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                                 reinterpret_cast<LPCWSTR>(handler), &owner) &&
                              owner == self;
            if (mine)
                haveCodeware = true;
            else
                vanilla.push_back(func);
        }
        if (!haveCodeware)
        {
            LogWarning("[VanillaApiCompat] ResRef.{}: Codeware's native not found, {} vanilla left.",
                       name.ToString(), vanilla.size());
            continue;
        }
        for (auto* func : vanilla)
            type->staticFuncs.Remove(func);
        LogInfo("[VanillaApiCompat] ResRef.{}: removed {} vanilla native(s), Codeware's kept.", name.ToString(),
                vanilla.size());
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
