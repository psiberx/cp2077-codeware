// SELFTEST R19. See MacR19.hpp.

#include "MacR19.hpp"

#include "MacDiag.hpp"
#include "MacAddressResolver.hpp"
#include "MacEngine.hpp"

#include "App/Callback/MacHookStats.hpp"
#include "App/Callback/CallbackSystem.hpp"
#include "App/Depot/ResourceDepot.hpp"
#include "App/Scripting/StackTrace.hpp"
#include "App/Callback/CallbackSystemHandler.hpp"
#include "App/Shared/ResourcePathRegistry.hpp"
#include "Core/Facades/Container.hpp"
#include "Red/Scripting.hpp"
#include "Red/Serialization.hpp"
#include "Core/Hooking/HookingAgent.hpp"

#include <atomic>
#include <cstdio>
#include <cstdlib>

namespace
{
std::atomic<int> s_checks{0};
std::atomic<int> s_failed{0};

// ---- B2: OnConstruct. CClass::CreateInstance is hooked (ScriptingService::OnMacCreateInstance); creating an instance of the
// scripted class CodewareMacConstructTest (tools/diag-scripts/CodewareMacDiag.reds) must run its script OnConstruct, which
// sets `constructed`. Creating a scripted handle is what Codeware does for services (ScriptableServiceContainer::Build).
std::atomic<int> s_constructRan{0};
std::atomic<int> s_constructed{0};

void ConstructTest()
{
    const int mode = Mac::R19OnConstructMode();
    if (mode == 0)
    {
        MAC_DIAG( "[selftest] R19 OnConstruct: dispatch is off (CODEWARE_MAC_ONCONSTRUCT), test skipped\n");
        return;
    }
    auto* type = Red::GetClass("CodewareMacConstructTest");
    if (!type)
    {
        MAC_DIAG( "[selftest] R19 OnConstruct: the script class CodewareMacConstructTest is not in the cache, test skipped\n");
        return;
    }

    s_constructRan.store(1);
    auto instance = Red::MakeScriptedHandle<Red::IScriptable>(type);
    if (!instance)
    {
        Mac::R19Check(false, "a scripted instance was created");
        return;
    }

    auto* flag = Red::GetPropertyPtr<bool>(instance.instance, "constructed");
    bool constructed = flag && *flag;
    MAC_DIAG( "[selftest] R19 OnConstruct: test instance=%p flag=%p\n", static_cast<void*>(instance.instance),
                 static_cast<void*>(flag));

    s_constructed.store(constructed ? 1 : 0);
    MAC_DIAG( "[selftest] R19 OnConstruct: property found=%d constructed=%d\n", flag ? 1 : 0, constructed ? 1 : 0);
    // The hook gave its temporary reference back: the new handle must be the only owner.
    const uint32_t strong = instance.refCount ? instance.refCount->strongRefs : 0;
    MAC_DIAG( "[selftest] R19 OnConstruct: handle strong=%u weak=%u\n", strong, instance.refCount ? instance.refCount->weakRefs : 0);
    Mac::R19Check(flag != nullptr, "the scripted class has its constructed property");
    Mac::R19Check(constructed, "CClass::CreateInstance ran OnConstruct on a scripted class");
    Mac::R19Check(strong == 1, "the OnConstruct hook left the new handle as the only owner");
}
}

namespace
{

// ---- B2: reflection, enums, clone, default virtuals. Everything here calls game functions through the SDK the way Codeware's
// own natives do, on the postLoadScripts thread, with test data on the stack or in handles that die at the end of the test.
void ReflectionTests()
{
    // CEnum on a Codeware enum (a Codeware CEnum object, so the call goes through the SDK inline into the game function):
    // value to string and back.
    if (auto* en = Red::GetEnum<App::CallbackRunMode>())
    {
        const auto once = static_cast<int64_t>(App::CallbackRunMode::Once);
        const auto oncePerTarget = static_cast<int64_t>(App::CallbackRunMode::OncePerTarget);

        int64_t value = once;
        Red::CString text;
        const bool toOk = en->ToString(&value, text);
        MAC_DIAG( "[selftest] R19 enum ToString(%lld) -> %d \"%s\"\n", static_cast<long long>(once), toOk ? 1 : 0, text.c_str());
        Mac::R19Check(toOk && std::strcmp(text.c_str(), "Once") == 0, "CEnum::ToString gives the enumerator name");

        int64_t parsed = 0;
        const bool fromOk = en->FromString(&parsed, Red::CString("OncePerTarget"));
        MAC_DIAG( "[selftest] R19 enum FromString(OncePerTarget) -> %d %lld\n", fromOk ? 1 : 0, static_cast<long long>(parsed));
        Mac::R19Check(fromOk && parsed == oncePerTarget, "CEnum::FromString parses the enumerator name from a (data, size) string");

        int64_t unknown = 77;
        Mac::R19Check(!en->FromString(&unknown, Red::CString("NoSuchEnumerator")) && unknown == 77,
                      "CEnum::FromString rejects an unknown name and leaves the value alone");
    }
    else
    {
        Mac::R19Check(false, "the Codeware CallbackRunMode enum is registered");
    }

    // CClass::GetProperties and TTypedClass IsEqual on a Codeware struct with three properties.
    if (auto* cls = Red::GetClass<App::StackTraceEntry>())
    {
        Red::DynArray<Red::CProperty*> props;
        cls->GetProperties(props);
        MAC_DIAG( "[selftest] R19 GetProperties(StackTraceEntry) -> %u properties\n", props.Size());
        Mac::R19Check(props.Size() == 3, "CClass::GetProperties lists the three properties of a Codeware struct");

        App::StackTraceEntry a(Red::CName("ClassA"), Red::CName("FuncA"), {});
        App::StackTraceEntry b(Red::CName("ClassA"), Red::CName("FuncA"), {});
        App::StackTraceEntry c(Red::CName("ClassA"), Red::CName("FuncB"), {});
        const bool same = cls->IsEqual(&a, &b);
        const bool different = cls->IsEqual(&a, &c);
        MAC_DIAG( "[selftest] R19 IsEqual(equal)=%d IsEqual(different)=%d\n", same ? 1 : 0, different ? 1 : 0);
        Mac::R19Check(same && !different, "TTypedClass IsEqual compares property by property");
    }
    else
    {
        Mac::R19Check(false, "the Codeware StackTraceEntry struct is registered");
    }

    // A game class: the properties of the whole chain, parent first.
    if (auto* cls = Red::GetClass("gameObject"))
    {
        Red::DynArray<Red::CProperty*> props;
        cls->GetProperties(props);
        uint32_t chain = 0;
        for (auto* c = cls; c; c = c->parent)
        {
            chain += c->props.Size();
        }
        MAC_DIAG( "[selftest] R19 GetProperties(gameObject) -> %u properties, own chain sum %u\n", props.Size(), chain);
        Mac::R19Check(props.Size() == chain && chain > 0, "CClass::GetProperties covers the class chain of a game class");
    }

    // Clone of a scripted object: a new object of the same class with the same field value.
    if (Mac::R19OnConstructMode() == 1)
    {
        if (auto* type = Red::GetClass("CodewareMacConstructTest"))
        {
            auto source = Red::MakeScriptedHandle<Red::ISerializable>(type);
            if (source)
            {
                auto* flag = Red::GetPropertyPtr<bool>(source.instance, "constructed");
                if (flag)
                    *flag = true;

                Red::Handle<Red::ISerializable> clone;
                Raw::ISerializable::Clone(clone, source);
                const bool ok = static_cast<bool>(clone) && clone.instance != source.instance && clone->GetType() == type;
                auto* cloneFlag = ok ? Red::GetPropertyPtr<bool>(clone.instance, "constructed") : nullptr;
                MAC_DIAG( "[selftest] R19 Clone: clone=%p source=%p sameType=%d field=%d\n", static_cast<void*>(clone.instance),
                             static_cast<void*>(source.instance), ok ? 1 : 0, cloneFlag && *cloneFlag ? 1 : 0);
                Mac::R19Check(ok, "ISerializable::Clone makes a new object of the same class");
                Mac::R19Check(cloneFlag && *cloneFlag, "the clone has the field value of the source");
            }
        }
    }

    // The default virtual stubs, reached through a Codeware native object (its vtable is the SDK's, so these are the SDK
    // defaults that forward to the game functions). The object has no owning resource.
    {
        auto object = Red::MakeHandle<App::ResourceDepot>();
        if (object)
        {
            const bool owned = object->sub_30();
            void* ownerValue = object->sub_C0(nullptr);
            MAC_DIAG( "[selftest] R19 default virtuals: sub_30=%d sub_C0=%p\n", owned ? 1 : 0, ownerValue);
            Mac::R19Check(owned, "ISerializable::sub_30 is true for an object without an owning resource");
            Mac::R19Check(ownerValue == nullptr, "ISerializable::sub_C0 is null for an object without an owning resource");
        }
        else
        {
            Mac::R19Check(false, "a Codeware native object was created");
        }
        // The object dies here: ~IScriptable runs IScriptable_DestructValueHolder, now the game function.
    }
}

// ---- B3: resource path registry and loader.
void ResourceTests()
{
    // The registry knows paths the game created at boot (the hook sees every ResourcePath::Create call).
    auto registry = Core::Resolve<App::ResourcePathRegistry>();
    if (registry)
    {
        const auto known = Red::ResourcePath(R"(base\sound\event\eventsmetadata.json)");
        const auto resolved = registry->ResolvePath(known);
        MAC_DIAG( "[selftest] R19 ResourcePathRegistry: eventsmetadata.json -> \"%s\" (create calls so far %llu)\n",
                     resolved.c_str(), static_cast<unsigned long long>(Mac::HookCount("ResourcePath_Create").calls.load()));
        Mac::R19Check(!resolved.empty(), "the registry resolves a path the game hashed at boot");

        const std::string mine = R"(mac\r19\registry\test.json)";
        const auto path = registry->RegisterPath(mine);
        Mac::R19Check(registry->ResolvePath(path) == mine, "RegisterPath and ResolvePath round-trip");
    }
    else
    {
        Mac::R19Check(false, "the ResourcePathRegistry feature exists");
    }

    // The loader singleton is where the data row says it is.
    const auto cell = reinterpret_cast<void* const*>(Red::MacGameBase() + 0x99DC690);
    auto* loader = Red::ResourceLoader::Get();
    MAC_DIAG( "[selftest] R19 ResourceLoader: cell=%p Get()=%p\n", *cell, static_cast<void*>(loader));
    Mac::R19Check(loader != nullptr && static_cast<void*>(loader) == *cell, "ResourceLoader::Get() is the pointer in the data cell");
}
}

void Mac::R19Check(bool aOk, const char* aWhat)
{
    s_checks.fetch_add(1);
    if (!aOk)
    {
        s_failed.fetch_add(1);
        MAC_DIAG( "[selftest] R19 FAIL %s\n", aWhat);
    }
}

void Mac::R19Summary(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    const int failed = s_failed.load();
    MAC_DIAG( "[selftest] R19 %s@%s (checks=%d failed=%d)\n", failed == 0 ? "PASS" : "FAIL", aWhen, s_checks.load(),
                 failed);
}

int Mac::R19OnConstructMode()
{
    static const int mode = [] {
        const char* v = std::getenv("CODEWARE_MAC_ONCONSTRUCT");
        if (!v)
            return 1; // on by default since r19g
        return v[0] == '0' ? 0 : 1;
    }();
    return mode;
}

void Mac::R19PostLoadScripts()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    ConstructTest();
    ReflectionTests();
    ResourceTests();
}

namespace
{
std::atomic<uint32_t> s_locCalls{0};
std::atomic<uint32_t> s_locWithResult{0};
std::atomic<uint32_t> s_locMaxEntries{0};
std::atomic<uint32_t> s_locWithText{0};
std::atomic<uint32_t> s_locKnownLanguage{0};
}

void Mac::R19NoteLocalization(uint32_t aEntries, uint32_t aWithText, bool aLanguageKnown)
{
    ++s_locCalls;
    if (aEntries > 0)
        ++s_locWithResult;
    if (aLanguageKnown)
        ++s_locKnownLanguage;
    uint32_t current = s_locMaxEntries.load();
    while (aEntries > current && !s_locMaxEntries.compare_exchange_weak(current, aEntries))
    {
    }
    if (aWithText > s_locWithText.load())
        s_locWithText.store(aWithText);
}

void Mac::R19CheckAtT50()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }

    // GetGameInstance: Lizzie's services call it from synthetic frames; every call must have been answered with the live one.
    const auto calls = App::MacHookStats::getGameInstanceCalls.load();
    const auto empty = App::MacHookStats::getGameInstanceEmpty.load();
    const auto live = App::MacHookStats::getGameInstanceRescued.load();
    MAC_DIAG( "[selftest] R19 GetGameInstance: calls=%llu live=%llu empty=%llu\n", static_cast<unsigned long long>(calls),
                 static_cast<unsigned long long>(live), static_cast<unsigned long long>(empty));
    Mac::R19Check(calls > 0, "the GetGameInstance hook was called");
    Mac::R19Check(empty == 0, "no GetGameInstance call returned an empty instance");

    // Localization: the hook on the game's LoadTexts is called for the onscreens resource of the game language, and the
    // Handle it hands to the observer is a real LocalizationPersistenceOnScreenEntries with entries that have text.
    const auto locCalls = s_locCalls.load();
    MAC_DIAG( "[selftest] R19 Localization: LoadTexts calls=%u withEntries=%u knownLanguage=%u maxEntries=%u firstWithText=%u\n",
                 locCalls, s_locWithResult.load(), s_locKnownLanguage.load(), s_locMaxEntries.load(), s_locWithText.load());
    Mac::R19Check(locCalls > 0, "the LoadTexts hook was called");
    Mac::R19Check(s_locMaxEntries.load() > 100, "LoadTexts returned an onscreens resource with more than 100 entries");
    Mac::R19Check(s_locWithText.load() > 0, "the onscreen entries carry texts");

    // The resource path hook has seen the engine's startup traffic.
    // With the ported ArchiveXL in the session the first plugin to start owns the one hook and fills the shared registry; the
    // shared counter sees every call whichever plugin owns the hook.
    const auto createdOwn = Mac::HookCount("ResourcePath_Create").calls.load();
    const auto created = std::max<uint64_t>(createdOwn, App::ResourcePathRegistry::SharedHitCount());
    MAC_DIAG( "[selftest] R19 ResourcePath_Create calls=%llu (own hook %llu)\n", static_cast<unsigned long long>(created),
                 static_cast<unsigned long long>(createdOwn));
    Mac::R19Check(created >= 1000, "the ResourcePath_Create hook saw the startup path hashing");
}
