#include "ScriptableServiceContainer.hpp"
#include "Red/Serialization.hpp"

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
            Red::CallVirtual(service, m_scriptsLoaded ? "OnReload" : "OnLoad");
        }
        else
        {
            if (serviceType->flags.isAbstract)
                continue;

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

void App::ScriptableServiceContainer::OnBeforeWorldDetach(Red::world::RuntimeScene* aScene)
{
    SaveState();
}

uint32_t App::ScriptableServiceContainer::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
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
    auto state = Red::MakeHandle<ScriptableServiceContainerState>();

    for (const auto& [_, service] : m_services)
    {
        state->services.PushBack(service);
    }

    try
    {
        Red::ObjectSerializer::SaveToFile(state, m_stateFilePath);
    }
    catch (std::exception& ex)
    {
        LogError(R"([ScriptableServiceContainer] Can't save state to "{}": {})",
                 m_stateFilePath.string(), ex.what());
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
