#pragma once

namespace Red::AddressLib
{
constexpr uint32_t Main = 3545369307;
constexpr uint32_t GetScriptGameInstance = 1559305924;

constexpr uint32_t CBaseEngine_InitEngine = 3273923080;

constexpr uint32_t CGameFramework_InitializeGameInstance = 4007601841;

constexpr uint32_t CMesh_GetAppearance = 773462733;

constexpr uint32_t CommunitySystem_Update = 1559565515;

constexpr uint32_t Entity_Attach = 4248638169;
constexpr uint32_t Entity_Detach = 2263681375;
constexpr uint32_t Entity_Dispose = 2515274237;
constexpr uint32_t Entity_Initialize = 3490519617;
constexpr uint32_t Entity_OnAssemble = 2182550867;
constexpr uint32_t Entity_Reassemble = 1560690857;
constexpr uint32_t Entity_Uninitialize = 3596356635;

constexpr uint32_t InkLayer_RegisterListener = 4792499;
constexpr uint32_t InkLayer_AttachWidgetTree = 2050958960;

constexpr uint32_t InkLogicController_OnInitialize = 2671382832;
constexpr uint32_t InkLogicController_OnUninitialize = 1159862457;
constexpr uint32_t InkLogicController_OnArrangeChildrenComplete = 3589084925;

constexpr uint32_t InkSpawner_FinishAsyncSpawn = 2488155854;

constexpr uint32_t InkSystem_Instance = 2755465343;
constexpr uint32_t InkSystem_ProcessCharacterEvent = 4284882427;
constexpr uint32_t InkSystem_ProcessInputEvents = 673454961;

constexpr uint32_t InkWidget_GetLayer = 1667176558;
constexpr uint32_t InkWidget_SetLayer = 2516523266;
constexpr uint32_t InkWidget_ScriptReparent = 492509908;
constexpr uint32_t InkWidget_ScriptAddChild = 3558023194;
constexpr uint32_t InkWidget_TriggerEvent = 3357288308;

constexpr uint32_t InkWidgetLibrary_AsyncSpawnFromExternal = 1396063719;
constexpr uint32_t InkWidgetLibrary_AsyncSpawnFromLocal = 118698863;
constexpr uint32_t InkWidgetLibrary_SpawnFromExternal = 506278179;
constexpr uint32_t InkWidgetLibrary_SpawnFromLocal = 1158555307;

constexpr uint32_t MeshAppearance_LoadMaterialSetupAsync = 1419388740;

constexpr uint32_t MorphTargetManager_ApplyMorphTarget = 633871992;

constexpr uint32_t NodeRef_Create = 3491172781;

constexpr uint32_t PersistentObject_InitializeState = 3442350580;

constexpr uint32_t PlayerSystem_OnPlayerSpawned = 2050111212; // cp::PlayerSystem::OnPlayerMainObjectSpawned

constexpr uint32_t PointOfInterestMappin_SetPhase = 803085170;

constexpr uint32_t QuestLoader_PhasePreloadCheck = 1567104722;

constexpr uint32_t QuestPhaseInstance_Initialize = 3423879019;
constexpr uint32_t QuestPhaseInstance_ExecuteGraph = 779107884;
constexpr uint32_t QuestPhaseInstance_ExecuteNode = 3227858325;

constexpr uint32_t QuestsSystem_CreateContext = 3144298192;

constexpr uint32_t RuntimeSystemWeather_SetWeatherByName = 2334794340;
constexpr uint32_t RuntimeSystemWeather_SetWeatherByIndex = 1821516328;

constexpr uint32_t ScriptBundle_dtor = 3993832650;

constexpr uint32_t ScriptValidator_CompareTypeName = 1327107674;

constexpr uint32_t VehicleSystem_ToggleGarageVehicle = 3027836941;
}
