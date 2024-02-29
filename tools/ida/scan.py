from cp77ida import Item, Group, Output, scan
from pathlib import Path


# Defines patterns and output files
def patterns():
    return [
        Output(filename="src/Red/Addresses/Direct.hpp", namespace="Red::Address", groups=[
            Group(functions=[
                Item(name="Main",
                     pattern="40 55 53 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? FF 15 ? ? ? ? E8"),
                Item(name="GetScriptGameInstance",
                     pattern="48 83 EC ? 48 FF 02 33 C9 48 8B 42 ? 48 85 C0 74 ? 48 BA 7B FF 43 56 41 00 00 00 48 39 10 75"),
            ]),
            Group(name="CBaseEngine", functions=[
                Item(name="InitEngine",
                     pattern="48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 48 8B FA 48 8B D9 E8 ? ? ? ? BA 02 00 00 00 33 C9 FF 15"),
            ]),
            Group(name="CGameFramework", functions=[
                Item(name="InitializeGameInstance",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 4C 8B 4A ? 48 8B D9 BF ? ? ? ? 4D 85 C9 74 ? 65 48 8B 04 25 ? ? ? ? 4D 8B 09 4C 8B 00 41 8A 41 ? 42 88  04 07 48 8B 01 4C 8B C2",
                     expected=2,
                     index=0),
            ]),
            Group(name="CommunitySystem", functions=[
                Item(name="Update",
                     pattern="48 89 5C 24 ? 55 56 57 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 8A DA 0F 29 74 24 ? 48 8D 91 ? ? ? ? 48 8B F1"),
            ]),
            Group(name="CMesh", functions=[
                Item(name="GetAppearance",
                     pattern="40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 83 38 00 74 ? 48 83 C4 ? 5B C3"),
            ]),
            Group(name="Entity", functions=[
                Item(name="Attach",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 60 C6 81 ? ? ? ? 03 48 8B F2 80 7A ? 00"),
                Item(name="Detach",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 C6 81 ? ? ? ? 05 E8 ? ? ? ? 66 83 64 24 ? 00"),
                Item(name="Dispose",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 8A 81 ? ? ? ? 48 8B F9 2C 02 3C 03 77 ? 48 8B 99"),
                Item(name="Initialize",
                     pattern="48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 8A 81 ? ? ? ? 4C 8D A1"),
                Item(name="OnAssemble",
                     pattern="48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 02 48 8B FA 48 89 41 ? 48 8B D9 48 8B 42 ? 48 89 41 ? 48 8B 42"),
                Item(name="Reassemble",
                     pattern="48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 56 41 57 48 8D 68 ? 48 81 EC ? ? ? ? 4C 8B F2 49 8B F9 48"),
                Item(name="Uninitialize",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 C6 81 ? ? ? ? 06 48 81 C1 ? ? ? ? E8"),
            ]),
            Group(name="InkLayer", functions=[
                Item(name="RegisterListener",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99 ? ? ? ? 48 8B E9 48 8B CB 48 8B F2 E8 ? ? ? ? 48 8B 46 08 33 FF 0F 57 C0 F3 0F 7F 44 24",
                     expected=2,
                     index=0),
                Item(name="AttachWidgetTree",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 83 65 ? 00 48 8D 05 ? ? ? ? 83 65 ? 00 48 8B FA 48 8B F1",
                     expected=2,
                     index=0),
            ]),
            Group(name="InkLogicController", functions=[
                Item(name="OnInitialize",
                     pattern="40 53 48 83 EC ? 48 8B 51 ? 48 8B D9 48 85 D2 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B CB"),
                Item(name="OnUninitialize",
                     pattern="40 53 48 83 EC ? 48 8B D9 48 8D 4C 24 ? E8 ? ? ? ? 48 8B CB 48 8B 10 E8 ? ? ? ? 48 8B CB 48 83 C4"),
                Item(name="OnArrangeChildrenComplete",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B F9 80 B8 ? ? ? ? 00 75 ? 80 3D ? ? ? ? 00"),
            ]),
            Group(name="InkSpawner", functions=[
                Item(name="FinishAsyncSpawn",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8B DA 48 8B 49 ? 48 81 C1 ? ? ? ? E8 ? ? ? ? 48 8B 13"),
            ]),
            Group(name="InkSystem", pointers=[
                Item(name="Instance",
                     pattern="45 33 FF 41 8B C7 B9 ? ? ? ? 87 87 ? ? ? ? 48 89 3D ? ? ? ? E8",
                     offset=20),
            ], functions=[
                Item(name="ProcessCharacterEvent",
                     pattern="48 89 5C 24 ? 44 89 44 24 ? 55 48 8B EC 48 83 EC 50 44 8B D2 48 8B D9 48 81 C1 ? ? ? ? 48 8D 55 ? E8"),
                Item(name="ProcessInputEvents",
                     pattern="48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 4C 8B EA 0F 29 78 ? 48 8B F9 44 0F 29 40 ?"),
            ]),
            Group(name="InkWidget", functions=[
                Item(name="GetLayer",
                     pattern="48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 48 8D 99 ? ? ? ? 48 8B FA 48 83 3B 00"),
                Item(name="SetLayer",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 48 81 C1 ? ? ? ? E8"),
                Item(name="ScriptReparent",
                     pattern="48 89 5C 24 08 48 89 74 24 18 48 89 7C 24 20 55 48 8B EC 48 83 EC 40 48 8B 02 48 8D 35 ? ? ? ? 48 83 62 30 00 4C 8D 45 E0 48 83 62 38 00",
                     expected=4,
                     index=0),
                Item(name="ScriptAddChild",
                     pattern="4C 8B DC 49 89 5B 08 49 89 73 18 57 48 83 EC 40 48 8B 02 4C 8D 15 ? ? ? ? 49 83 63 10 00 49 8B F0 48 83 62 30 00"),
                Item(name="TriggerEvent",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 49 8B F8 E8 ? ? ? ? 48 85 C0 75 ? 32 DB 48 8B CF E8"),
            ]),
            Group(name="InkWidgetLibrary", functions=[
                Item(name="AsyncSpawnFromExternal",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 49 8B D9 48 8D 54 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 45 33 C9 4C 8B C3 48 8B D7 E8"),
                Item(name="AsyncSpawnFromLocal",
                     pattern="48 83 EC ? 4C 8B D2 49 8B D0 E8 ? ? ? ? 48 85 C0 74 ? 45 8A C1 49 8B D2 48 8B C8 E8 ? ? ? ? B0 01 48 83 C4 ? C3"),
                Item(name="SpawnFromExternal",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 49 8B D9 48 8D 54 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 4C 8B C3 48 8B D7 E8"),
                Item(name="SpawnFromLocal",
                     pattern="40 53 48 83 EC 20 48 8B DA 49 8B D0 E8 ? ? ? ? 48 85 C0 74 ? 48 8B D3 48 8B C8 E8 ? ? ? ? 48 8B C3"),
            ]),
#             Group(name="IScriptable", functions=[
#                 Item(name="InitializeScriptData",
#                      pattern="48 89 51 30 4C 89 41 38 C3"),
#             ]),
            Group(name="MeshAppearance", functions=[
                Item(name="LoadMaterialSetupAsync",
                     pattern="48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 65 48 8B 04 25 ? ? ? ? 48 8B D9 B9 ? ? ? ? 0F 57 C0"),
            ]),
            Group(name="MorphTargetManager", functions=[
                Item(name="ApplyMorphTarget",
                     pattern="48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 48 83 EC ? 33 F6 0F 29 70 ? 40 88 70 ? 0F 28 F3 49 8B F8"),
            ]),
            Group(name="NodeRef", functions=[
                Item(name="Create",
                     pattern="48 89 5C 24 ? 44 88 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 8B 72 08 4C 8B F1 85 F6"),
            ]),
            Group(name="PersistentObject", functions=[
                Item(name="InitializeState",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 8B 52 ? E8 ? ? ? ? 48 8B F0"),
            ]),
            Group(name="PlayerSystem", functions=[
                Item(name="OnPlayerSpawned",
                     pattern="48 89 5C 24 18 48 89 74 24 20 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC 50 48 8B DA 48 8B F9"),
            ]),
            Group(name="PointOfInterestMappin", functions=[
                Item(name="SetPhase",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B D9 44 8B F2"),
            ]),
            Group(name="QuestsSystem", functions=[
                Item(name="CreateContext",
                     pattern="48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 56 48 83 EC ? 48 8B 41 ? 4C 8D 91 ? ? ? ? 48 89 44 24"),
            ]),
            Group(name="QuestLoader", functions=[
                Item(name="PhasePreloadCheck",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 48 8B FA 48 8B 49 ? E8 ? ? ? ? 32 DB 84 C0 74"),
            ]),
            Group(name="QuestPhaseInstance", functions=[
                Item(name="Initialize",
                     pattern="4C 89 4C 24 ? 4C 89 44 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 33 C0 48 8D 9A ? ? ? ? 89 81 ? ? ? ? 48 8D 75"),
                Item(name="ExecuteGraph",
                     pattern="4C 8B DC 49 89 5B ? 49 89 6B ? 49 89 73 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 49 8B 40 ? 4D 8B E9"),
                Item(name="ExecuteNode",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B 02 48 8B E9 48 8B CA 49 8B D9 49 8B F8 48 8B F2"),
            ]),
            Group(name="RuntimeSystemWeather", functions=[
                Item(name="SetWeatherByName",
                     pattern="48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B DA"),
                Item(name="SetWeatherByIndex",
                     pattern="48 8B C4 48 89 58 ? 48 89 70 ? 55 57 41 56 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 8B F2 0F 29 78 ? 48 8D 54 24"),
            ]),
            Group(name="ScriptBundle", functions=[
                Item(name="dtor",
                     pattern="40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8D 8B ? ? ? ? FF 15 ? ? ? ? 48 8D 8B ? ? ? ? E8"),
            ]),
            Group(name="ScriptValidator", functions=[
                Item(name="CompareTypeName",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B DA 48 8B F9 48 3B CA 75 ? 40 B6 01"),
            ]),
            Group(name="VehicleSystem", functions=[
                Item(name="ToggleGarageVehicle",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 48 8D 91 ? ? ? ? 41 8A F8 48 8D 4C 24 ? E8"),
            ]),
        ]),
    ]


# Defines base output dir
def output_dir():
    cwd = Path(__file__).resolve().parent
    return cwd.parent.parent  # 2 levels up


scan(patterns(), output_dir(), __file__)
