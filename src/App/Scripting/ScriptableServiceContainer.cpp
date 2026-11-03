#include "ScriptableServiceContainer.hpp"
#if defined(__APPLE__)
#include "MacDiag.hpp"
#endif
#include "Red/Serialization.hpp"

#if defined(__APPLE__)
#include <cstdio>
#include <cstdlib>
#include "MacEngine.hpp"
#include "MacR19.hpp"
#include "MacR21.hpp"

namespace Mac
{
// macos/MacR16b.cpp. Self-test (CODEWARE_MAC_DIAG=1 only), runs once.
void R16bSelfTest();
}
#endif

App::ScriptableServiceContainer::ScriptableServiceContainer(const std::filesystem::path& aStateDir)
    : m_stateFilePath((aStateDir / Red::GetTypeNameStr<ScriptableServiceContainer>().data()).replace_extension(".dat"))
{
    LoadState();
}

void App::ScriptableServiceContainer::OnInitializeScripts()
{
    Red::DynArray<Red::CClass*> serviceTypes;
    Red::CRTTISystem::Get()->GetClasses(Red::GetClass<ScriptableService>(), serviceTypes);

    for (auto serviceType : serviceTypes)
    {
        const auto& serviceIt = m_services.find(serviceType->name);

        if (serviceIt != m_services.end())
        {
            auto& service = serviceIt.value();
#if defined(__APPLE__)
            std::fprintf(stderr, "[cw] service %s %s\n", m_scriptsLoaded ? "OnReload" : "OnLoad", serviceType->name.ToString());
#endif
            Red::CallVirtual(service, m_scriptsLoaded ? "OnReload" : "OnLoad");
        }
        else
        {
            if (serviceType->flags.isAbstract)
                continue;

#if defined(__APPLE__)
            std::fprintf(stderr, "[cw] service OnLoad %s\n", serviceType->name.ToString());
#endif
            auto service = Red::ToHandle<ScriptableService>(serviceType->CreateInstance());
            Red::CallVirtual(service, "OnLoad");
            if (m_scriptsLoaded)
            {
                Red::CallVirtual(service, "OnReload");
            }
            m_services.emplace(serviceType->name, std::move(service));
        }
    }

    m_scriptsLoaded = true;
}

void App::ScriptableServiceContainer::OnInitializeGameInstance()
{
    for (const auto& [serviceType, service] : m_services)
    {
        Red::CallVirtual(service, "OnInitialize");
    }

    SaveState();
}

#if defined(__APPLE__)
void App::ScriptableServiceContainer::MacInitializeGameInstance(const char* aVia)
{
    if (m_gameInstanceInitialized.exchange(true))
        return;

    MAC_DIAG("[cw] services OnInitialize via %s\n", aVia);

    try
    {
        OnInitializeGameInstance();
    }
    catch (const std::exception& ex)
    {
        std::fprintf(stderr, "[cw] services OnInitialize exception %s\n", ex.what());
    }
    catch (...)
    {
        std::fprintf(stderr, "[cw] services OnInitialize exception\n");
    }
}

void App::ScriptableServiceContainer::OnWorldAttached(Red::world::RuntimeScene* aScene)
{
    // Fallback: only when the InitializeGameInstance hook did not run (it was refused).
    MacInitializeGameInstance("first world attach (fallback, the InitializeGameInstance hook did not run)");

    // Self-tests of the runtime scene (CODEWARE_MAC_DIAG=1 only). The runtime scene is known here.
    try
    {
        Mac::RuntimeSceneSelfTest(aScene);
        Mac::R21WorldAttachTests(aScene);
    }
    catch (...)
    {
        MAC_DIAG("[selftest] R18 runtime scene exception\n");
    }

    // Self-test (CODEWARE_MAC_DIAG=1 only). The state file SaveState wrote at OnInitializeGameInstance is read back and compared.
    if (Mac::DiagEnabled())
    {
        try
        {
            MacPersistenceSelfTest();
        }
        catch (...)
        {
            MAC_DIAG("[selftest] R19 persistence exception\n");
        }
    }

    // Self-test (CODEWARE_MAC_DIAG=1 only). The game systems and their vtables exist here.
    try
    {
        Mac::R16bSelfTest();
    }
    catch (...)
    {
        MAC_DIAG( "[selftest] R16b exception\n");
    }
}
#endif

#if defined(__APPLE__)
// Self-test (CODEWARE_MAC_DIAG=1 only). The round trip of the production code with its own file next to the real state file (which stays: the next
// boot's LoadState reads it, the restore path a player meets on the second start). SaveStateTo writes a state with every live
// service, ReadFromFile reads it back the way LoadState does, the services are compared with the live ones, the test file is deleted.
void App::ScriptableServiceContainer::MacPersistenceSelfTest()
{
    static std::atomic<bool> s_done{false};
    if (s_done.exchange(true))
        return;

    const auto testPath = std::filesystem::path(m_stateFilePath).replace_filename("ScriptableServiceContainerSelfTest.dat");
    std::error_code error;
    std::filesystem::remove(testPath, error);

    SaveStateTo(testPath);

    const bool exists = std::filesystem::exists(testPath, error);
    const auto size = exists ? std::filesystem::file_size(testPath, error) : 0;
    MAC_DIAG( "[selftest] R19 persistence: %s exists=%d bytes=%llu (production file %s exists=%d)\n",
                 testPath.string().c_str(), exists ? 1 : 0, static_cast<unsigned long long>(size), m_stateFilePath.string().c_str(),
                 std::filesystem::exists(m_stateFilePath, error) ? 1 : 0);
    Mac::R19Check(exists && size > 8, "SaveState wrote the state file");

    if (exists)
    {
        Red::Handle<ScriptableServiceContainerState> state;
        Red::ObjectSerializer::ReadFromFile(state, testPath);

        const bool read = static_cast<bool>(state);
        const size_t count = read ? state->services.Size() : 0;
        MAC_DIAG( "[selftest] R19 persistence: read back state=%d services=%zu live=%zu\n", read ? 1 : 0, count,
                     m_services.size());
        Mac::R19Check(read, "ReadFromFile gave the state object back");
        Mac::R19Check(read && count == m_services.size(), "the state holds every live service");

        bool same = read;
        if (read)
        {
            for (const auto& service : state->services)
            {
                if (!service || m_services.find(service->GetType()->name) == m_services.end())
                    same = false;
            }
        }
        Mac::R19Check(same, "every read back service is a live service type");

        std::filesystem::remove(testPath, error);
        MAC_DIAG( "[selftest] R19 persistence: test file removed (%d)\n", error ? 0 : 1);
    }
}
#endif

void App::ScriptableServiceContainer::OnBeforeWorldDetach(Red::world::RuntimeScene* aScene)
{
    SaveState();
}

uint32_t App::ScriptableServiceContainer::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
#if defined(__APPLE__)
    // MAC-NOT-YET: the save dispatches SaveState through JobQueue(group) only with CODEWARE_MAC_SAVE_JOBS=1; the default is the R16b inline call (SaveState works since R19, but the job dispatch inside a real save is not tested yet, and a job adds risk to saves). The job family itself is exercised at the menu by Mac::JobDispatchTest.
    static const bool s_viaJobs = [] {
        const char* v = std::getenv("CODEWARE_MAC_SAVE_JOBS");
        return v && v[0] == '1';
    }();
    static std::atomic<int> s_saves{0};
    const int n = s_saves.fetch_add(1) + 1;
    MAC_DIAG("[cw] R18 OnBeforeGameSave #%d: SaveState %s\n", n, s_viaJobs ? "dispatched through JobQueue(group)" : "inline (job dispatch off)");
    if (!s_viaJobs)
    {
        SaveState();
        return 0;
    }
#endif
    Red::JobQueue{aJobGroup}.Dispatch([this]{ SaveState(); });
    return 0;
}

void App::ScriptableServiceContainer::OnUninitialize()
{
    for (const auto& [serviceType, service] : m_services)
    {
        Red::CallVirtual(service, "OnUninitialize");
    }

    SaveState();

    m_services.clear();
}

void App::ScriptableServiceContainer::LoadState()
{
#if defined(__APPLE__)
    // R19. State persistence is on (ObjectSerializer rows mapped, Mac ABI in src/Red/Serialization.hpp). The self-test
    // MacPersistenceSelfTest round-trips the state file at the menu.
    MAC_DIAG("[cw] R19 LoadState: %s\n", m_stateFilePath.string().c_str());
#endif

    std::error_code error;
    if (!std::filesystem::exists(m_stateFilePath, error))
        return;

    auto state = Red::MakeHandle<ScriptableServiceContainerState>();

    try
    {
        Red::ObjectSerializer::ReadFromFile(state, m_stateFilePath);
    }
    catch (std::exception& ex)
    {
        LogError(R"([ScriptableServiceContainer] Can't load state from "{}": {})",
                 m_stateFilePath.string(), ex.what());
    }

    if (state)
    {
#if defined(__APPLE__)
        {
            size_t restored = 0;
            for (const auto& service : state->services)
            {
                if (service)
                    ++restored;
            }
            MAC_DIAG("[cw] R19 LoadState: read %zu services from the file (%zu not null)\n", static_cast<size_t>(state->services.Size()),
                     restored);
        }
#endif
        for (auto& service : state->services)
        {
            if (service)
            {
                m_services.emplace(service->GetType()->name, std::move(service));
            }
        }
    }
}

void App::ScriptableServiceContainer::SaveState()
{
#if defined(__APPLE__)
    SaveStateTo(m_stateFilePath);
}

void App::ScriptableServiceContainer::SaveStateTo(const std::filesystem::path& aPath)
{
#endif
    auto state = Red::MakeHandle<ScriptableServiceContainerState>();

    for (const auto& [_, service] : m_services)
    {
        state->services.PushBack(service);
    }

    try
    {
#if defined(__APPLE__)
        Red::ObjectSerializer::SaveToFile(state, aPath);
#else
        Red::ObjectSerializer::SaveToFile(state, m_stateFilePath);
#endif
    }
    catch (std::exception& ex)
    {
        LogError(R"([ScriptableServiceContainer] Can't save state to "{}": {})",
#if defined(__APPLE__)
                 aPath.string(), ex.what());
#else
                 m_stateFilePath.string(), ex.what());
#endif
    }
}

Red::Handle<App::ScriptableService> App::ScriptableServiceContainer::GetService(Red::CName aType)
{
    auto it = m_services.find(aType);

    if (it == m_services.end())
        return {};

    return it.value();
}

Red::Handle<App::ScriptableServiceContainer>& App::ScriptableServiceContainer::Build(
    const std::filesystem::path& aStateDir)
{
    if (!s_self)
    {
        s_self = Red::MakeHandle<ScriptableServiceContainer>(aStateDir);
    }

    return s_self;
}

Red::Handle<App::ScriptableServiceContainer>& App::ScriptableServiceContainer::Get()
{
    return s_self;
}
