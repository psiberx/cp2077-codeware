#include "MacAddressResolver.hpp"

#include "MacEngine.hpp"

#include <RED4ext/Relocation.hpp>

#include <cstdio>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace
{
// RVAs from the Mac image (Steam 2.3.1). 0xC0DE000x ids are Mac-only (job bodies, ScriptGameInstance builder) and are
// not in cyberpunk2077_addresses.json. The others are SDK hashes of Codeware's Library.hpp.
const std::unordered_map<uint32_t, uintptr_t>& MacRows()
{
    static const std::unordered_map<uint32_t, uintptr_t> rows = {
        {0xC0DE0001, 0x1209038}, // ResourceSerializer_MacLoadJob. Entry runs after deserialization.
        {0xC0DE0002, 0x12092e0}, // ResourceSerializer_MacPostLoadJob. Entry runs after post-load.
        {4248638169, 0x529EC50},  // Entity_Attach. void(Entity*, void* ctx). Not 0xC99378 (inside the prologue).
        {3491172781, 0x1B17694}, // NodeRef_Create. Mac ABI uint64_t(const char*, uint32_t, bool).
        {1559305924, 0x16A5BA8}, // GetScriptGameInstance. The GetGameInstance script native (void(ctx, frame, out, type)).
        {0xC0DE0003, 0x16AA1F0}, // MacScriptGameInstanceCtor. void(ScriptGameInstance* out, GameInstance*). Mac-only id.
        {0xC0DE0012, 0x1219C30}, // ResourceSerializer_MacJobDecode (R81). bool(name, source {data, size}, destination, capacity). Function start (the callers' 4-byte thunk 0x1219C2C jumps here); called by the deserialize job 0x1207ED4 and six buffer loaders.
        {0xC0DE0013, 0x1B1F1C8}, // WorldInstancedMeshNodeInstance_MacAttach (R82). bool(worldInstancedMeshNodeInstance*, attach context*). Slot 0x168 of the instance vtable 0x78E53F0 (constructor 0x1B21384), called by the generic node instance attach 0x1BBF9F4; reads node mesh entry [instance +0x88] +0x20 unchecked.
        // R18 B0. Engine timing hooks and the framework's GameInstance job. Entry and body matched against the Windows twin.
        {3273923080, 0x4D7EFB8}, // CBaseEngine_InitEngine. bool(CBaseEngine&, CGameOptions&). Windows 0x7CB080: same init-stage strings and options+0xB1.
        {3729789488, 0x4D7FBA8}, // CBaseEngine_LoadGatheredResources. bool(CBaseEngine&). Windows 0x303460: virtual slot 0xD0 (Mac 0xD8), helper call, bool.
        {4007601841, 0x1578050}, // CGameFramework_InitializeGameInstance. Job body void(closure, group); the first word of the closure is the CGameFramework, and the job frees the closure. Windows 0x16145C.
        {3993832650, 0x111CC00}, // ScriptBundle_dtor. void(ScriptBundle*). Windows 0x7B7C18: same member destruction order (+0x138 ... +0x90; Mac 2.5.0: +0xD8 ... down, the bundle gained 8 bytes in front).
        // R18 B0/B1. Entity lifecycle, input, player, vehicle, component and sound rows. Each was matched against the Windows twin
        // by a read-only agent (strings, field offsets, callees, a caller on both sides) and rated by tools/addr-match/check-rows.py.
        {3490519617, 0x19AA7D8},  // Entity_Initialize. void(Entity*, JobQueue&, EntityInitializeRequest*). RequestComponents and four job schedulers are inlined. Windows 0x8B0190.
        {2296260874, 0x19A8040},  // Entity_RequestComponents. Identity matches Windows 0x8B116C, but Mac has no caller (inlined into Initialize and Reassemble): never hooked.
        {489494088, 0x19B74B0},   // EntityBuilder_ExtractComponentsJob. void(EntityBuilderJobParams*, void*). Windows 0x1CD4A8.
        {437791594, 0x19B3E70},   // EntityBuilder_ScheduleExtractComponentsJob. Mac void(EntityBuilder*, job::Builder&): the Windows signature differs. Declared only. Windows 0x8AC678.
        {2182550867, 0x19AA048},  // Entity_Assemble. void(Entity*, Request*). Not 0xC97E24, which is the base class no-op. Windows 0x8AB708.
        {1560690857, 0x19A7A30},  // Entity_Reassemble. void(Entity*, a2, CName, u64, DynArray&, Handle&), all six in registers. Windows 0xC27FD8.
        {3596356635, 0x19AB2D4},  // Entity_Uninitialize. void(Entity*). Not 0xC992C0 (base no-op). Dispose inlines it. Windows 0x402F74.
        {2515274237, 0x19AB7F8},  // Entity_Dispose. void(Entity*). Windows 0x8B5540.
        {2263681375, 0x19AB4DC},  // Entity_Detach. void(Entity*). Not 0xC996BC (base no-op). Windows 0x1B3A1C.
        {525805301, 0x20A096C},  // Entity_ResolveRecordID. Mac uint64_t TweakDBID(Entity* unused, PopulationSpawnParameter*): no out pointer. Windows 0x7280AC.
        {673454961, 0x426C760},  // InkSystem_ProcessInputEvents. void(InkSystem*, a2, RawInputBuffer&). Windows 0x39B8E8.
        {2050111212, 0xFFFCB8}, // PlayerSystem_OnPlayerSpawned. x0..x3 map to the Windows rcx..r9. Windows 0xA1452C.
        {1883248814, 0x2B3DAC0}, // VehicleController_ToggleAuxLights. void(controller, bool enable, uint lightType). Not the thunk 0x12E6F40. Windows 0x274564.
        {3370191745, 0x19B95F4},  // IComponent_Toggle. void(IComponent*, bool). Ten instructions, tail call through a virtual slot. Windows 0x45A944.
        {2635337807, 0x8ECE4D0}, // InkSystem_Instance. Data: the global that holds the InkSystem pointer. Windows .data 0x3495C70.
        {3961524856, 0x51D4F30},  // SoundBankManager_ReadSoundBanksJson. bool(manager). The body, not the wrapper 0xDC8CF8. Windows 0x7D4844.
        {1576079097, 0x4DDF5C0},  // JobHandle_Wait. bool(JobHandle*), plain blocking wait. Windows 0x2AC294.
        // R19 B2. Object serialization. All three return through x8 on Mac (the Windows signatures take the out object first).
        {1944983789, 0x1086858}, // ObjectSerializer_Prepare. void(ObjectSerializer*, Params*). Hooked at the entry for the magic size limit. Windows 0xD0B690.
        {2646156567, 0x48852D8}, // ObjectSerializer_WriteToBuffer. DataBuffer(const Handle*, uint32 flags, uint32 sizeLimit), result through x8. Windows 0x2A672B8.
        {125247621,  0x488518C}, // ObjectSerializer_ReadFromStrean. Handle<ISerializable>(BaseStream*, CClass*), result through x8. Windows 0x4946F4.
        {2601784524, 0x1067f5c}, // ISerializable_Clone. Handle<ISerializable>(const Handle*), result through x8. Windows 0x74ED60.
        // R19 B3. Resource paths, the resource bank and localization.
        {3998356057, 0x106C8C4}, // ResourcePath_Create. uint64_t(const char* text, uint32 size): the hash comes back in x0. The same entry the NCC ArchiveXL hooked with the Windows shape and crashed. Windows 0x1DF644.
        {2288918343, 0x10E4454}, // ResourceBank_ForgetResource. Handle<CResource>(bank value, path), result through x8. Windows 0x261A4C.
        {3550098299, 0x1C2B6DC}, // Localization_LoadOnScreens. Handle<PersistenceOnScreenEntries>(path), result through x8. Not the sibling 0x2F67BE0 (subtitle map). Windows 0x261018.
        // R15. Script validator and opcode table. Static analysis in R14, hooks in R15.
        {898639042, 0x11A7E28},  // ScriptValidator_Validate. bool(validator, ScriptBundle*, report).
        {560604283, 0x11A8F30},  // ScriptValidator_ValidateProperty. bool(unused, ScriptProperty*, CProperty*).
        {4224523662, 0x11A9108}, // ScriptValidator_CompareType. bool(CBaseRTTIType* native, ScriptType* script). Plain call.
        {961751128, 0x9A5C940},  // ScriptOpCodes_Handlers. Data: 8-byte handler table, zero in the file, filled at run time.
        {2070546748, 0x1203FA8}, // ScriptOpCodes_Register. Fills the table (one call to 0x21FD4B8 per opcode). Not hooked.
        // R20 B4. Ink UI. Each row was matched against the Windows twin by a read-only agent (strings, callers on both sides, field
        // offsets) and rated by tools/addr-match/check-rows.py. Mac signatures are in src/Red/InkLibrary.hpp and InkCore.hpp.
        {1158555307, 0x435402C}, // InkWidgetLibrary_SpawnFromLocal. Handle<WidgetLibraryItemInstance>(lib&, CName), the Handle through x8. Windows 0x57F9C0.
                                 // 2.5 entry the game calls (0x42CE2C4, 0x42D30BC): tests InkSpawner_ControllerInjectionEnabled, else the inline lookup.
                                 // 0x435413C is the same body without the test, reached only from the flag-set path (0x4155D18, 0x4155DF8).
        {506278179, 0x435424C},  // InkWidgetLibrary_SpawnFromExternal. Handle(lib&, ResourcePath, CName), the Handle through x8. Windows 0x9FB618.
        {118698863, 0x4353a7c},  // InkWidgetLibrary_AsyncSpawnFromLocal. bool(lib&, InkSpawningInfo&, CName, bool flag). Windows 0x57F26C.
        {2342073570, 0x4353a7c}, // InkWidgetLibrary_AsyncSpawnFromLocal: the 2.5 hash of the same function (psiberx/cp2077-codeware#63, Windows 0x208F2E0). Mac signature already carries the bool.
        {1396063719, 0x4353D74}, // InkWidgetLibrary_AsyncSpawnFromExternal. bool(lib&, InkSpawningInfo&, ResourcePath, CName, bool flag). Windows 0x9FB2A8.
        {225197914, 0x4353D74},  // InkWidgetLibrary_AsyncSpawnFromExternal: the 2.5 hash of the same function (psiberx/cp2077-codeware#63, Windows 0x208F250).
        {2698985195, 0x4368F34}, // InkSpawner_FinishAsyncSpawn. void(InkSpawningContext*, Handle<WidgetLibraryItemInstance>&): the call operator of the std::function behind InkSpawningInfo. Windows 0xFA63F0.
        {4097515464, 0x4368F34}, // InkSpawner_FinishAsyncSpawn: the 2.5 hash of the same function (psiberx/cp2077-codeware#63, Windows 0x209FBE0).
        {2890273101, 0x9D03E78}, // InkSpawner_ControllerInjectionEnabled. Data: one byte in __DATA,__common (zerofill). The four spawn functions above
                                 // and FinishAsyncSpawn load it first (ldrb, cmp #1) and take the "Item:Controller" path when it is 1. Its only
                                 // two stores (0x4156600 sets 1, 0x4156610 sets 0) are never called or referenced, so in 2.5.0 it stays 0.
        {2671382832, 0x41ABBF4}, // InkLogicController_OnInitialize. void(controller): the base implementation shared by 82 vtables (slot 0x110). Windows 0x581514.
        {1159862457, 0x41ABD94}, // InkLogicController_OnUninitialize. void(controller): base implementation (slot 0x118). Windows 0x4A2B40.
        {3589084925, 0x41ABEA4}, // InkLogicController_OnArrangeChildrenComplete. void(controller): base implementation (slot 0x120). Windows 0x32B78C.
        {1667176558, 0x439C7E8}, // InkWidget_GetLayer. Handle<inkLayerProxy>(inkWidget*): the Handle through x8, no out argument. Windows 0x2EE72C.
        {2516523266, 0x43A0288}, // InkWidget_SetLayer. void(inkWidget*, const Handle<inkLayerProxy>*). Windows 0x4FCD4C.
        {492509908, 0x43A7644},  // InkWidget_ScriptReparent. Native script function body void(this, CStackFrame*, ret, retType), hooked HookAfter. Windows 0xF0F724.
        {3558023194, 0x43931A0}, // InkWidget_ScriptAddChild (inkCompoundWidget.AddChild). Native script function body, hooked HookAfter. Windows 0x2218FE4.
        {3357288308, 0x43ACF40}, // InkWidget_TriggerEvent. bool(manager = widget+0x50, CName, Handle<Event> passed indirectly); the caller owns the copy. Windows 0x89A86C.
        {4792499, 0x42D4728},    // InkLayer_RegisterListener. void(inkLayer*, const Handle<IScriptable>*). Not the sibling 0x48DC420. Windows 0x881848.
        {2050958960, 0x42D3A38}, // InkLayer_AttachWidgetTree. void(inkLayer*, const Handle<inkWidget>*, const Handle<inkLayerProxy>*): walker and visitor inlined. Not the clone 0x48D6834. Windows 0x581248.
        {4284882427, 0x427028c}, // InkSystem_ProcessCharacterEvent. bool(InkSystem*, EInputKey, EInputAction). Windows 0xC225C0.
        // R21 B5. World, quest and the update registrar. Each row was matched against the Windows twin by a read-only agent and rated by
        // tools/addr-match/check-rows.py.
        // MAC-NOT-YET: CNamePool_AddCString (4292220681) is not applicable on Mac. Its Windows table address is an unrelated vtable slot and the SDK overload Add(const CString&) resolves to CNamePool_AddCstr (0x3452DDC) with c_str(), which gives the same hash; no row and no hook.
        // MAC-NOT-YET: QuestsSystem_CreateContext (3144298192) has no standalone Mac function (clang inlined the wrapper into the 18 callers); Raw::QuestsSystem::CreateContext calls the QuestContext constructor (Mac-only id 0xC0DE0011) with the quest system fields.
        {2840271332, 0x1A2BB60},  // RuntimeEntityRegistry_RegisterEntity. bool(registry, Entity*): true when newly inserted. Windows 0x8B57F4.
        {3878623943, 0x1A2BF84},  // RuntimeEntityRegistry_UnregisterEntity. bool(registry, Entity*). Windows 0x8B5310.
        {1576214475, 0x1A3D6FC},  // RuntimeSystemEntity_AttachEntity. void(system, const AttachRequest*): a two instruction thunk (ldr x0,[x0,#0x48]; b 0xCF6EBC), called not hooked. Windows 0x8B6928.
        {1737563910, 0x1A3D704},  // RuntimeSystemEntity_DetachEntity. void(system, const Handle<Entity>*): a two instruction thunk. Windows 0xB839B8.
        {2597397686, 0x1A3D704},  // RuntimeSystemEntity_DetachEntity: the 2.5 hash of the same function (psiberx/cp2077-codeware#63, Windows 0x74A8B8). The Mac callee has no reason argument.
        {1239092911, 0x40075E8}, // TagSystem_AssignTag. void(red::TagSystem* = GameTagSystem + 0x48, EntityID, CName). Windows 0x42559C.
        {1875775378, 0x4007B40}, // TagSystem_UnassignTag. void(red::TagSystem*, EntityID, CName). Windows 0xFF1AD8.
        {1559565515, 0x472C880}, // CommunitySystem_Update. void(CommunitySystem*, bool). Windows 0x3F226C.
        {1471948702, 0x1A71ABC},  // RuntimeSystemWeather_GetEnvironmentDefinition. Handle<worldEnvironmentDefinition>(system): the Handle through x8. Windows 0x1DB070.
        {1821516328, 0x1A70298},  // RuntimeSystemWeather_SetWeatherByIndex. (system, uint32 index, CName source, uint32 a5, uint32 priority, float blend in s0). Windows 0xA0592C.
        {2987664085, 0x1A70298},  // RuntimeSystemWeather_SetWeatherByIndex: the 2.5 hash of the same function (psiberx/cp2077-codeware#63, Windows 0x2127C70). Mac gained a bool in w5.
        {2334794340, 0x1A730FC},  // RuntimeSystemWeather_SetWeatherByName. bool(system, CName weather, CName source, uint32 a5, uint32 priority, float blend in s0). Windows 0x13CC1AC.
        {2679119876, 0x1A71548},  // RuntimeSystemWeather_GetWeatherState. Handle<worldWeatherState>(system): the Handle through x8. Windows 0xA06808.
        {803085170, 0x3140998},  // PointOfInterestMappin_SetPhase. bool(mappin, phase): vtable slot 0x1D0 of PointOfInterestMappin on Mac (0x1C8 on Windows). Windows 0x27A6F20.
        {3227858325, 0x280DF0C}, // QuestPhaseInstance_ExecuteNode. uint8(phase, node*, QuestContext&, const Socket&, DynArray<Socket>&). Windows 0x58E5A8.
        {3423879019, 0x280C128}, // QuestPhaseInstance_Initialize. (phase, QuestContext&, const Handle<resource>&, Handle<graph>&, const NodePath&, w5 = node id): the args that were on the Windows stack are in registers. Reached by a tail branch from the phase factory. Windows 0x257724.
        {779107884, 0x2805874},  // QuestPhaseInstance_ExecuteGraph. uint8(phase, QuestContext&, const WeakHandle<node>&, const Socket&, bool, DynArray<Socket>&). Windows 0x9481D8.
        {0xC0DE0011, 0x280379C}, // QuestContext_ctor (Mac-only id). QuestsSystem_CreateContext is inlined in the 18 Mac callers; this is the constructor it forwards to: ctx = ctor(ctx, a3, a4, a5, a6, *(qs+0xE8), qs+0xA8, qs+0xB8, qs+0x78, qs+0x1D0, *(qs+0x2C8), *(qs+0x40)). Windows 0x258F70.
        // R21 B5 entity rows (read-only agents, check-rows).
        {633871992, 0x197F17C},   // MorphTargetManager_ApplyMorphTarget. void(manager, CName target, CName region, float s0, bool w3): w3 is a live flag on Mac (the Windows function ignores its fifth argument; all nine game callers pass 0). Windows 0x1607FC.
        {1828854026, 0x19545C8},  // IPlacedComponent_SetTransform. void(component, const WorldTransform*): a frameless leaf that tail-branches to 0xC91DD0. Windows 0x574FC8.
        {2912168594, 0x199E498},  // VisualController_LoadDependencies. JobHandle(VisualController*, w1 = a3): the JobHandle through x8. Windows 0x36B8E8.
        {3007126651, 0x519C4B0},  // CMesh_FindAppearance. Handle<MeshAppearance>*(CMesh*, CName): the pointer comes back in x0, not x8. Windows 0x3CA158.
        {773462733, 0x519E118},   // CMesh_GetAppearance. Windows 0x3CA128. (0xE19A1C is the shim that calls FindAppearance with the default name.)
        {3442350580, 0x16F3714}, // PersistentObject_InitializeState. void(object, params): hooked HookBefore at the entry, called for the entity's own PersistentObject and once per component. Windows 0x84BA8C.
        // R21 B5/B6 player, render and physics rows.
        {1159928678, 0x2AA79A8}, // VehicleGarageComponent_LoadSummonSetup. void(garage). The Windows table address (0x126DF78) is an RTTI type getter; the real function is Windows 0x126BF78 (it reads the 27 Vehicle.summon_setup flats).
        {3027836941, 0x2BBA088}, // VehicleSystem_ToggleGarageVehicle. bool(system, const GarageVehicleID*, bool): virtual (Windows slot 0x298, Mac 0x2A0), called directly. Windows 0x14FCFC8.
        {2996308699, 0x4FE0FB8}, // RenderData_Release. void(object): the generic intrusive release (refcount at +8, slot 8 on zero), a 9 instruction leaf: called, never hooked. Windows 0x1E6EB0.
        {2394822845, 0x4583398}, // PhysicsTraceResult_GetHitObject. Handle<ISerializable>(w0 = resultID, w1 = index): the strong Handle through x8. Not the weak variant 0x409274C. Windows 0x23F29C.
        {3068279668, 0x19F2F3C},  // EntitySpawner_SpawnEntity. SharedPtr<EntitySpawnerToken>(spawner, const EntitySpawnerRequest&): the SharedPtr through x8, no result argument. Called, not hooked. Windows 0x8B24B0.
        {552341017, 0x19F6CA8},   // EntitySpawnerToken_dtor. void(token): releases the entity Handle (+0x10) and the SharedPtr (+0), frees nothing; 0xCE0DD0 is a one instruction thunk to it, not to be hooked. Windows 0xCD921C.
        {2091718968, 0x19F6E34},  // EntitySpawnerToken_GetWaitHandle. JobHandle*(token). Not called by Codeware. Windows 0x8B2F6C.
        {1419388740, 0x51A3C24},  // MeshAppearance_LoadMaterialSetupAsync. Handle<MeshAppearance>(appearance, w1 = a3): the Handle through x8, no out argument. Windows 0x21A670.
        {1679234269, 0x51A31D0},  // MeshAppearance_ReleaseReference. void(appearance): the same lock, release and map clear as MeshAppearanceEx::ResetMaterialCache. Windows 0x21AA4C.
        {1790971865, 0x4FE4CA0}, // RenderProxy_SetVisibility. void(proxy, bool): a 13 instruction leaf that tail-branches to UpdateVisibility, called not hooked. Windows 0x27FEBC.
        // R16a. SDK hashes the vendored SDK table lacks. Shared with the SDK header overlay (see CMakeLists.txt).
#include "MacSdkRows.inc"
    };
    return rows;
}
}

uintptr_t Support::MacAddressResolver::ResolveAddress(uint32_t aAddressID)
{
    // R18. Hashes with a plugin-owned stand-in (the engine pointer slot, the EngineTime frequency).
    if (const auto standIn = Mac::StandInFor(aAddressID))
    {
        return standIn;
    }

    const auto& rows = MacRows();
    const auto it = rows.find(aAddressID);
    if (it != rows.end())
    {
        return Red::MacGameBase() + it->second;
    }

    // The SDK resolver holds the shared Mac rows (CRTTISystem_Get, TweakDB, CClass, function constructors). In this
    // build it also falls back to the trap table (MacTrap.cpp) for a hash that has no row anywhere: the returned
    // address is a stub that logs "[cw] not on Mac yet: <name>" on its first call and returns zero. Only an id that
    // is not in the table at all (a Mac-only id without a row) comes back as 0.
    return RED4ext::UniversalRelocBase::Resolve(aAddressID);
}
