from cp77ida import Item, Group, Output, scan
from pathlib import Path


# Defines patterns and output files
def patterns():
    return [
        Output(filename="src/Red/Addresses.hpp", namespace="Red::Addresses", groups=[
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
            Group(name="Entity", functions=[
                Item(name="Attach",
                     pattern=""),
                Item(name="Detach",
                     pattern=""),
                Item(name="Dispose",
                     pattern=""),
                Item(name="Initialize",
                     pattern=""),
                Item(name="OnAssemble",
                     pattern=""),
                Item(name="Reassemble",
                     pattern=""),
                Item(name="Uninitialize",
                     pattern=""),
            ]),
            Group(name="InkLayer", functions=[
                Item(name="RegisterListener",
                     pattern="48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99 ? ? ? ? 48 8B E9 48 8B CB 48 8B F2 E8 ? ? ? ? 48 8B 46 08 33 FF 0F 57 C0 F3 0F 7F 44 24",
                     expected=2,
                     index=0),
                Item(name="AttachWidgetTree",
                     pattern="48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 83 65 ? 00 48 8D 05 ? ? ? ? 83 65 ? 00 48 8B FA 48 8B F1 48 89 45 ? BA 00 04 00 00",
                     expected=2,
                     index=1),
            ]),
            Group(name="InkLogicController", functions=[
                Item(name="OnInitialize",
                     pattern=""),
                Item(name="OnUninitialize",
                     pattern=""),
                Item(name="OnArrangeChildrenComplete",
                     pattern=""),
            ]),
            Group(name="InkSpawner", functions=[
                Item(name="FinishAsyncSpawn",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8B DA 48 8B 49 ? 48 81 C1 ? ? ? ? E8 ? ? ? ? 48 8B 13"),
            ]),
            Group(name="InkSystem", pointers=[
                Item(name="Instance",
                     pattern="",
                     offset=15),
            ], functions=[
                Item(name="ProcessCharacterEvent",
                     pattern="48 89 5C 24 ? 44 89 44 24 ? 55 48 8B EC 48 83 EC 50 44 8B D2 48 8B D9 48 81 C1 ? ? ? ? 48 8D 55 ? E8"),
                Item(name="ProcessInputEvents",
                     pattern="48 8B C4 48 89 58 ? 55  56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 48 8B F9 0F 29 78"),
            ]),
            Group(name="InkWidget", functions=[
                Item(name="GetLayer",
                     pattern=""),
                Item(name="SetLayer",
                     pattern=""),
                Item(name="ScriptReparent",
                     pattern=""),
                Item(name="ScriptAddChild",
                     pattern="",
                     expected=17),
                Item(name="TriggerEvent",
                     pattern="",
                     expected=2,
                     index=1),
            ]),
            Group(name="InkWidgetLibrary", functions=[
                Item(name="AsyncSpawnFromExternal",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 49 8B D9 48 8D 54 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 45 33 C9 4C 8B C3 48 8B D7 E8"),
                Item(name="AsyncSpawnFromLocal",
                     pattern="48 83 EC ? 4C 8B D2 49 8B D0 E8 ? ? ? ? 48 85 C0 74 ? 45 8A C1 49 8B D2 48 8B C8 E8 ? ? ? ? B0 01 48 83 C4 ? C3"),
                Item(name="SpawnFromExternal",
                     pattern="48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 49 8B D9 48 8D 54 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 4C 8B C3 48 8B D7 E8"),
                Item(name="SpawnFromLocal",
                     pattern="40 53 48 83 EC 20 48 8B DA 49 8B D0 E8 ? ? ? ? 48 85 C0 74 ? 48 8B D3 48 8B C8 E8"),
            ]),
            Group(name="IScriptable", functions=[
                Item(name="InitializeScriptData",
                     pattern="48 89 51 30 4C 89 41 38 C3"),
            ]),
            Group(name="NodeRef", functions=[
                Item(name="Create",
                     pattern=""),
            ]),
            Group(name="PersistentObject", functions=[
                Item(name="InitializeState",
                     pattern=""),
            ]),
            Group(name="PlayerSystem", functions=[
                Item(name="OnPlayerSpawned",
                     pattern=""),
            ]),
            Group(name="ScriptBundle", functions=[
                Item(name="dtor",
                     pattern=""),
            ]),
            Group(name="ScriptValidator", functions=[
                Item(name="CompareTypeName",
                     pattern=""),
            ]),
            Group(name="VehicleSystem", functions=[
                Item(name="ToggleGarageVehicle",
                     pattern=""),
            ]),
        ]),
    ]


# Defines base output dir
def output_dir():
    cwd = Path(__file__).resolve().parent
    return cwd.parent.parent  # 2 levels up


scan(patterns(), output_dir(), __file__)
