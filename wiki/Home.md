Version: 1.18.0

## Lifecycle

### Scriptable services

Services are singletons that created on scripts initialization and, 
unlike scriptable systems, live between game sessions.
To create your own service, you have to define a class derived from `ScriptableService`.

```swift
class MyService extends ScriptableService {
  private cb func OnLoad() {
    FTLog("Scripts loaded");
  }

  private cb func OnReload() {
    FTLog("Scripts reloaded");
  }

  private cb func OnInitialize() {
    FTLog("Game instance initialized, can access game systems");
  }

  private cb func OnUninitialize() {
    FTLog("Game is shutting down");
  }
}
```

Service instance can be accessed using service container:

```swift
let myService = GameInstance.GetScriptableServiceContainer().GetService(n"MyService") as MyService;
```

**Note:** if you declare `MyService` in a module, you must include the full path of the module to get the service:

```swift
module MyModule.Services

class MyService extends ScriptableService {
  // ...
}

let myService = GameInstance.GetScriptableServiceContainer().GetService(n"MyModule.Services.MyService") as MyService;
```

Service properties marked as `persistent` will keep their state forever. 
Unlike scriptable systems, service state storage is not tied to save files.

```swift
struct MyStats {
  public persistent let counter: Int32;
}

class MyService extends ScriptableService {
  private persistent let stats: MyStats;

  private cb func OnLoad() {
    this.stats.counter += 1;
    FTLog(s"The game launched \(this.stats.counter) time(s) since installing the mod");
  }
}
```

Persistence is available for all types except `String`, `ResRef`, `Variant`.
In case of objects, only fields marked as `persistent` are restored, 
and unmarked fields are reset to defaults on each game launch.
It's safe to change persistent data structure at any time.

> **Referencing game objects**  
> Be careful with storing references to game objects in services. Most objects must be disposed when game session ends.  
> An unreleased reference can interfere with normal object disposal and lead to bugs such as disappearing sounds or crashes.

### Game events

Callback system allows you to listen to various game events 
and in some cases alter game behavior and/or modify related game objects:

| Event Name            | Event Type             | Description                                                                                        |
|:----------------------|:-----------------------|:---------------------------------------------------------------------------------------------------|
| `Resource/Load`       | `ResourceEvent`        | Fired when resource and its dependencies have been loaded, but no post-processing is done yet.     |
| `Resource/PostLoad`   | `ResourceEvent`        | Fired when all post-processing is complete and resource is ready to be passed to the requester.    |
| `Session/BeforeStart` | `GameSessionEvent`     | Fired when a new session starts and game systems begin initialization.                             |
| `Session/Start`       | `GameSessionEvent`     | Fired when game systems are initialized, including scriptable systems.                             |
| `Session/Ready`       | `GameSessionEvent`     | Fired when session data is loaded and all entities are initialized and spawned.                    |
| `Session/BeforeEnd`   | `GameSessionEvent`     | Fired when session is going to end, but all game objects are still available.                      |
| `Session/End`         | `GameSessionEvent`     | Fired when game systems begin to dispose game objects and other session data.                      |
| `Session/BeforeSave`  | `GameSessionEvent`     | Fired right before saving and is guaranteed to prevent saving until callback is finished.          |
| `Session/AfterSave`   | `GameSessionEvent`     | Fired right after saving.                                                                          |
| `Session/Pause`       | `GameSessionEvent`     | Fired when game is paused.                                                                         |
| `Session/Resume`      | `GameSessionEvent`     | Fired when game is resumed.                                                                        |
| `Entity/Extract`      | `EntityBuilderEvent`   | Fired when all entity parts are extracted from `.ent` and `.app` to assemble the entity object.    |
| `Entity/Assemble`     | `EntityLifecycleEvent` | Fired when entity is assembled from extracted parts. Entity ID is not assigned yet.                |
| `Entity/Initialize`   | `EntityLifecycleEvent` | Fired when entity and its components are intializing. Entity ID is assigned at this stage.         |
| `Entity/Reassemble`   | `EntityLifecycleEvent` | Fired when components dynamically added or removed from entity. For example, when you equip items. |
| `Entity/Attach`       | `EntityLifecycleEvent` | Fired when entity is added to the world. Can be fired multiple times during entity lifetime.       |
| `Entity/AfterAttach`  | `EntityLifecycleEvent` | Fired when attachment process is finished for entity.                                              |
| `Entity/Detach`       | `EntityLifecycleEvent` | Fired when entity is removed from the world. Can be fired multiple times during entity lifetime.   |
| `Entity/Uninitialize` | `EntityLifecycleEvent` | The last stage of entity lifecycle before disposal.                                                |
| `Component/Toggle`    | `EntityComponentEvent` | Fired after component is enabled or disabled.                                                      |
| `Input/Key`           | `KeyInputEvent`        | Catches keyboard, mouse and controller button inputs.                                              |
| `Input/Axis`          | `AxisInputEvent`       | Catches mouse movements and controller axis inputs.                                                |
| `InkWidget/Spawn`     | `inkWidgetSpawnEvent`  | Fired when widget is spawned from widget library and before it's added to parent widget.           |

When defining a callback, you can specify event targets for which the callback should be fired:

| Target Definition                          | Compatible Event Types                       | Description                                                 |
|:-------------------------------------------|:---------------------------------------------|:------------------------------------------------------------|
| `ResourceTarget.Path(ResRef)`              | `ResourceEvent`                              | Selects resource by path.                                   |
| `ResourceTarget.Type(CName)`               | `ResourceEvent`                              | Selects resource by type name, e.g. `n"entEntityTemplate"`. |
| `EntityTarget.ID(EntityID)`                | `EntityBuilderEvent`, `EntityLifecycleEvent` | Selects entity by entity ID.                                |
| `EntityTarget.Type(CName)`                 | `EntityBuilderEvent`, `EntityLifecycleEvent` | Selects entity by type name, e.g. `n"PlayerPuppet"`.        |
| `EntityTarget.RecordID(TweakDBID)`         | `EntityBuilderEvent`, `EntityLifecycleEvent` | Selects entity by record ID, e.g. `t"Character.Panam"`.     |
| `EntityTarget.Template(ResRef)`            | `EntityBuilderEvent`, `EntityLifecycleEvent` | Selects entity by template path.                            |
| `EntityTarget.Appearance(CName)`           | `EntityBuilderEvent`, `EntityLifecycleEvent` | Selects entity by appearance name.                          |
| `EntityTarget.Definition(ResRef)`          | `EntityBuilderEvent`                         | Selects entity by appearance resource.                      |
| `EntityTarget.Definition(ResRef, CName)`   | `EntityBuilderEvent`                         | Selects entity by appearance resource and definition name.  |
| `DynamicEntityTarget.Tag(CName)`           | `EntityLifecycleEvent`                       | Selects entity created using dynamic entity system by tag.  |
| `StaticEntityTarget.Tag(CName)`            | `EntityLifecycleEvent`                       | Selects entity created using static entity system by tag.   |
| `ComponentTarget.ID(CRUID)`                | `EntityComponentEvent`                       | Selects component by ID.                                    |
| `ComponentTarget.Name(CName)`              | `EntityComponentEvent`                       | Selects component by name.                                  |
| `InputTarget.Key(EInputKey)`               | `KeyInputEvent`                              | Selects input event by key.                                 |
| `InputTarget.Key(EInputKey, EInputAction)` | `KeyInputEvent`                              | Selects input event by key in combination with action.      |
| `InputTarget.Axis(EInputKey)`              | `AxisInputEvent`                             | Selects input event by axis.                                |
| `inkWidgetTarget.Library(ResRef, CName)`   | `inkWidgetSpawnEvent`                        | Selects widget library path and library item name.          |
| `inkWidgetTarget.Controller(CName)`        | `inkWidgetSpawnEvent`                        | Selects widget by game controller type.                     |

This example injects custom menu scenario when `pregame_menu.inkmenu` is accessed by the game:

```swift
class MyService extends ScriptableService {
  private cb func OnLoad() {
    GameInstance.GetCallbackSystem()
      .RegisterCallback(n"Resource/Ready", this, n"OnMenuResourceReady")
      .AddTarget(ResourceTarget.Path(r"base\\gameplay\\gui\\fullscreen\\main_menu\\pregame_menu.inkmenu"));
  }

  private cb func OnMenuResourceReady(event: ref<ResourceEvent>) {
    let resource = event.GetResource() as inkMenuResource;
    ArrayPush(resource.scenariosNames, n"MenuScenario_NewGamePlus");
  }
}
```

You can make callback to auto unregister after being fired by calling `.SetRunMode(CallbackRunMode.Once)`.

```swift
class MySystem extends ScriptableSystem {
  private func OnAttach() {
    GameInstance.GetCallbackSystem().RegisterCallback(n"Entity/Attached", this, n"OnPanamFirstSpawn")
      .AddTarget(EntityTarget.RecordID(t"Character.Panam"))
      .SetRunMode(CallbackRunMode.Once);
  }

  private cb func OnPanamFirstSpawn(event: ref<EntityLifecycleEvent>) {
    FTLog("Panam spawned");
  }
}
```

If you set `.SetRunMode(CallbackRunMode.OncePerTarget)` mode, callback will be auto unregistered 
after being fired for each listed target. 
In this example, callback will be fired just once for each of F1-F4 keys:

```swift
class MySystem extends ScriptableSystem {
  private func OnAttach() {
    GameInstance.GetCallbackSystem().RegisterCallback(n"Input/Key", this, n"OnKeyInput")
      .AddTarget(InputTarget.Key(EInputKey.IK_F1))
      .AddTarget(InputTarget.Key(EInputKey.IK_F2))
      .AddTarget(InputTarget.Key(EInputKey.IK_F3))
      .AddTarget(InputTarget.Key(EInputKey.IK_F4))
      .SetRunMode(CallbackRunMode.OncePerTarget);
  }

  private cb func OnKeyInput(evt: ref<KeyInputEvent>) {
    FTLog(s"Pressed \(evt.GetKey())");
  }
}
```

When defined inside scriptable service, callback stays registered until you manually unregister it. 
When defined in other contexts, callback is auto removed at the end of the session.
You can change this behavior by explicitly calling 
`.SetLifetime(CallbackLifetime.Forever)` or `.SetLifetime(CallbackLifetime.Session)` for callback.

Callback system can be accessed before game instance is initialized.

### Custom events

Callback system can also be used by mods to dispatch their own events.

First of all you have to define event object:

```swift
module MyMod

public class CustomEvent extends CallbackSystemEvent {
    private let data: Int32;

    public func GetData() -> Int32 {
        return this.data;
    }

    static func Create(data: Int32) -> ref<CustomEvent> {
        let event = new CustomEvent();
        event.data = data;
        return event;
    }
}
```

To listen for event you have to use full class name `MyMod.CustomEvent` as event name:

```swift
import MyMod.*

class CustomEventListener extends ScriptableService {
    private cb func OnLoad() {
        GameInstance.GetCallbackSystem().RegisterCallback(n"MyMod.CustomEvent", this, n"OnCustomEvent");
    }

    private cb func OnCustomEvent(event: ref<CustomEvent>) {
        FTLog(s"\(event.GetEventName()) \(event.GetData())");
    }
}
```

To dispatch event you have to create event object and pass it to callback system:

```swift
GameInstance.GetCallbackSystem().DispatchEvent(CustomEvent.Create(123));
```

### Reference

- [ScriptableSerivce](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Scripting/ScriptableSerivce.reds)
- [CallbackSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/CallbackSystem.reds)
- [ResourceEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/ResourceEvent.reds)
- [GameSessionEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/GameSessionEvent.reds)
- [EntityLifecycleEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/EntityLifecycleEvent.reds)
- [KeyInputEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/KeyInputEvent.reds)
- [AxisInputEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/AxisInputEvent.reds)
- [inkWidgetSpawnEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Callback/Events/InkWidgetSpawnEvent.reds)

## World

### Spawning dynamic entities

Dynamic entity system allows you to spawn and manage your entities.
It's focused on dynamic entities such as puppets and vehicles, but can also be used on basic entities.

To create a new entity you have to define an entity spec using next options:

| Option           |      Type      |  Default   | Description                                                                                                                                           |
|:-----------------|:--------------:|:----------:|:------------------------------------------------------------------------------------------------------------------------------------------------------|
| `recordID`       |  `TweakDBID`   |     –      | The record to spawn. Can be any `SpawnableObject` record. Must be used for spawning fully functional NPCs and vehicles.                               |
| `templatePath`   |    `ResRef`    |     –      | The entity template (`.ent`) to spawn. Can't be used together with `recordID`. NPCs and vehicles may not function properly if spawned using template. |
| `appearanceName` |    `CName`     |   `None`   | Initial appearance. If not set, then appearance will be determined based on the record and/or entity template.                                        |
| `position`       |   `Vector4`    |   `Zero`   | Initial spawn position.                                                                                                                               |
| `orientation`    |  `Quaternion`  | `Identity` | Initial spawn rotation.                                                                                                                               |
| `persistState`   |     `Bool`     |  `false`   | If `true`, the entity state will be saved and restored on next game load, otherwise it will be reset to the initial state on every spawn.             |
| `persistSpawn`   |     `Bool`     |  `false`   | If `true`, the entity will be automatically spawned on next game load, otherwise it will exist until the end of the session.                          |
| `alwaysSpawned`  |     `Bool`     |  `false`   | If `true`, the entity will be kept always spawned during the game session, otherwise it will only spawn when player is around.                        |
| `spawnInView`    |     `Bool`     |   `true`   | If `true`, the entity will spawn even if player sees the spawn position, otherwise it will wait until player will look away.                          |
| `active`         |     `Bool`     |   `true`   | If `true`, the entity will spawn on creation, otherwise it will be registered in the system without spawning.                                         |
| `tags`           | `array<CName>` |    `[]`    | Initital tags associated with the entity, that can be used to identify individual entities or control group of entities.                              |

Entities with either `persistState` or `persistSpawn` option enabled are stored in the save file and can be reused on next game load.

When `persistState` is `true`, the entity receives persistent ID, that will never change until entity is deleted.
You can safely store persistent ID and use it to access the entity.
When `persistState` is `false`, the entity receives temporary ID, that will change on every game load.
You can only use temporary ID until the end of the current session.
Alternatively you can use tags instead of generated IDs to manage entities.

The next example spawns 3 entities on game load, but only if they weren't spawned before in this playthrough,
otherwise entities will be restored in their last saved state.

```swift
class MySpawnHandler extends ScriptableSystem {
  private let m_entitySystem: wref<DynamicEntitySystem>;
  private let m_callbackSystem: wref<CallbackSystem>;
  private let m_player: wref<GameObject>;
  private let m_handled: Bool;

  private func OnAttach() {
    this.m_entitySystem = GameInstance.GetDynamicEntitySystem();
    this.m_callbackSystem = GameInstance.GetCallbackSystem();

    // Register event listener for all entities with MyMod tag.
    this.m_callbackSystem.RegisterCallback(n"Entity/Attached", this, n"OnEntityAttached")
      .AddTarget(DynamicEntityTarget.Tag(n"MyMod"));
    this.m_callbackSystem.RegisterCallback(n"Entity/Detach", this, n"OnEntityDetached")
      .AddTarget(DynamicEntityTarget.Tag(n"MyMod"));

    // At this point player instance is not yet initialized.
    // We wait until earliest event when we can access player.
    // For new game, it will be OnPlayerAttach callback.
    // For loaded save, it will be OnRestored callback.
    this.m_handled = false;
  }

  private func OnRestored(saveVersion: Int32, gameVersion: Int32) {
    if !this.m_handled {
      this.HandleSpawning();
    }
  }

  private func OnPlayerAttach(request: ref<PlayerAttachRequest>) {
    if !this.m_handled {
      this.HandleSpawning();
    }
  }

  private cb func OnEntityAttached(event: ref<EntityLifecycleEvent>) {
    FTLog(s"Entity Attached \(EntityID.GetHash(event.GetEntity().GetEntityID()))");
  }

  private cb func OnEntityDetached(event: ref<EntityLifecycleEvent>) {
    FTLog(s"Entity Detached \(EntityID.GetHash(event.GetEntity().GetEntityID()))");
  }

  private func HandleSpawning() {
    this.m_handled = true;
    this.m_player = GetPlayer(this.GetGameInstance());

    // Simple check if we're in the main menu world.
    if GameInstance.GetSystemRequestsHandler().IsPreGame() {
      FTLog("We're in main menu");
      return;
    }

    // Check if entities with MyMod tag already present in the system.
    // Since we spawn persistent entities, they will be restored for a playthrough,
    // in which we already spawned our entities once.
    if this.m_entitySystem.IsPopulated(n"MyMod") {
      FTLog("Entities restored");
      return;
    }

    // Extra check if there's enough space in front of the player to spawn our entities.
    if !this.HasSpaceForSpawning() {
      FTLog("Can't create entities, there's no space");
      return;
    }

    let npcSpec = new DynamicEntitySpec();
    npcSpec.recordID = t"Character.spr_animals_bouncer1_ranged1_omaha_mb";
    npcSpec.appearanceName = n"random";
    npcSpec.position = this.GetPosition(4.0, -45.0);
    npcSpec.orientation = this.GetOrientation(-40.0);
    npcSpec.persistState = true;
    npcSpec.persistSpawn = true;
    npcSpec.tags = [n"MyMod"];

    let carSpec = new DynamicEntitySpec();
    carSpec.recordID = t"Vehicle.v_sport2_quadra_type66";
    carSpec.appearanceName = n"quadra_type66__basic_bulleat";
    carSpec.position = this.GetPosition(5.5, 0.0);
    carSpec.orientation = this.GetOrientation(90.0);
    carSpec.persistState = true;
    carSpec.persistSpawn = true;
    carSpec.tags = [n"MyMod", n"MyMod.Car"];

    let deviceSpec = new DynamicEntitySpec();
    deviceSpec.templatePath = r"base\\gameplay\\devices\\drop_points\\drop_point.ent";
    deviceSpec.position = this.GetPosition(5.0, 45.0);
    deviceSpec.orientation = this.GetOrientation(225.0);
    deviceSpec.persistState = true;
    deviceSpec.persistSpawn = true;
    deviceSpec.tags = [n"MyMod"];

    this.m_entitySystem.CreateEntity(npcSpec);
    this.m_entitySystem.CreateEntity(carSpec);
    this.m_entitySystem.CreateEntity(deviceSpec);

    FTLog("Entities created");
  }

  private func HasSpaceForSpawning() -> Bool {
    return !IsEntityInInteriorArea(this.m_player)
        && SpatialQueriesHelper.HasSpaceInFront(this.m_player, 0.1, 10.0, 10.0, 2.0);
  }

  private func GetDirection(angle: Float) -> Vector4 {
    return Vector4.RotateAxis(this.m_player.GetWorldForward(), new Vector4(0, 0, 1, 0), 
                              angle / 180.0 * Pi());
  }

  private func GetPosition(distance: Float, angle: Float) -> Vector4 {
    return this.m_player.GetWorldPosition() + this.GetDirection(angle) * distance;
  }

  private func GetOrientation(angle: Float) -> Quaternion {
    return EulerAngles.ToQuat(Vector4.ToRotation(this.GetDirection(angle)));
  }
}
```

### Spawning static entities

Static entity system has a similar set of functions as dynamic entity system, 
but it's optimized for spawning static entities that usually spawned by world nodes.
Unlike dynamic entity system, it doesn't manage persistent state and distance based visibility.
It's only job is to spawn/despawn and attach/detach entities on demand in the most simple way.

To spawn new entity you have to define an entity spec using next options:

| Option           |      Type      |  Default   | Description                                                                                                                               |
|:-----------------|:--------------:|:----------:|:------------------------------------------------------------------------------------------------------------------------------------------|
| `templatePath`   |    `ResRef`    |     –      | The entity template (`.ent`) to spawn. NPCs and vehicles may not function properly if spawned using template.                             |
| `appearanceName` |    `CName`     |   `None`   | Initial appearance. If not set, the default appearance from entity template will be used.                                                 |
| `position`       |   `Vector4`    |   `Zero`   | Initial spawn position.                                                                                                                   |
| `orientation`    |  `Quaternion`  | `Identity` | Initial spawn rotation.                                                                                                                   |
| `attached`       |     `Bool`     |   `true`   | If `true`, the entity will be automatically attached on creation, otherwise it will stay detached until explicitly `AttachEntity()` call. |
| `tags`           | `array<CName>` |    `[]`    | Initital tags associated with the entity, that can be used to identify individual entities or control group of entities.                  |

```swift
let ladderSpec = new StaticEntitySpec();
ladderSpec.templatePath = r"base\\gameplay\\devices\\ladder\\appearances\\10m_gen_default.en";
ladderSpec.position = GetPosition();
ladderSpec.orientation = GetOrientation();
ladderSpec.tags = [n"MyLadder"];

let entitySystem = GameInstance.GetStaticEntitySystem();
let entityID = entitySystem.SpawnEntity(ladderSpec);
```

You can manage entities by their IDs or associated tags.

```swift
entitySystem.DetachTagged(n"MyLadder");
entitySystem.AttachTagged(n"MyLadder");
entitySystem.DespawnEntity(entityID);
```

### Controlling weather

You can control the weather using new `SetWeather()` method:

```swift
let weatherSystem = GameInstance.GetWeatherSystem(GetGameInstance());
weatherSystem.SetWeather(n"24h_weather_rain", 10.0, 5);
```

The second parameter `blendTime` controls the smoothness of the weather transition.
Depending on the area and current weather cycle, it may be necessary to pass a higher priority 
as the third parameter for the weather to take effect.

To release the weather and allow it to return to its normal cycle, call `ResetWeather()` method:

```swift
weatherSystem.ResetWeather();
```

To immediately restore the weather for the area without waiting for the next cycle, 
set parameter `forceRestore` to `true`:

```swift
weatherSystem.ResetWeather(true);
```

### Controlling nodes and variants

You can control world state like quest and scene nodes do.
With custom streaming sectors and variants, you can quickly activate and deactive group of nodes. 

```swift
let worldStateSystem = GameInstance.GetWorldStateSystem();

worldStateSystem.ToggleNode(ToNodeRef("$/03_night_city/se1/loc_ma_bls_ina_se1_13_prefab3CX3BZA/loc_ma_bls_ina_se1_13_openworld_prefabA6C6LTI"), true);
worldStateSystem.ToggleVariant(ToNodeRef("#loc_ma_bls_gas_station_small_v2_interior_v1_deco_v1"), "robbery", true)
```

### Controlling communities

```swift
let worldStateSystem = GameInstance.GetWorldStateSystem();

// Activate/deactivate entire communities
worldStateSystem.ActivateCommunity(ToNodeRef("#bls_ina_se1_foodshop_03_com"));
worldStateSystem.DeactivateCommunity(ToNodeRef("#de_pac_cvi_03_com"));

// Activate/deactivate specific community entries
worldStateSystem.ActivateCommunity(ToNodeRef("#bls_ina_se1_foodshop_03_com"), n"shop_keeper");
worldStateSystem.DeactivateCommunity(ToNodeRef("#bls_ina_se1_foodshop_03_com"), n"shop_keeper");

// Set specific phase for a community entry
worldStateSystem.SetCommunityPhase(ToNodeRef("#bls_ina_se1_foodshop_03_com"), n"shop_keeper", n"working");
```

You can also access community objects to inspect their state:

```swift
let community = worldStateSystem.GetCommunity(ToNodeRef("#bls_ina_se1_foodshop_03_com"));
if IsDefined(community) {
    let entries = community.GetEntries();
    for entry in entries {
        FTLog(s"Community entry: \(entry.GetName()) - Active: \(entry.IsActive())");
    }
}
```

### Controlling population spawners

```swift
let worldStateSystem = GameInstance.GetWorldStateSystem();

// Activate/deactivate population spawners
worldStateSystem.ActivatePopulationSpawner(ToNodeRef("#mws_wat_02_iguana"));
worldStateSystem.DeactivatePopulationSpawner(ToNodeRef("#mws_wat_02_iguana"));
```

You can access spawner objects to inspect spawner state:

```swift
let spawner = worldStateSystem.GetPopulationSpawner(ToNodeRef("#mws_wat_02_iguana"));
if IsDefined(spawner) {
    let appearanceName = spawner.GetAppearanceName();
    let active = spawner.IsActive();
    FTLog(s"Spawner appearance: \(appearanceName) - Active: \(active)");
}
```

### Accessing mappins

```swift
let mappins: array<ref<IMappin>> = GameInstance.GetMappinSystem(GetGameInstance()).GetAllMappins();
```

### Spatial queries

You can now extract world node or entity from `TraceResult` you get from ray casting.

```swift
public static func GetLookAtTarget() -> ref<ISerializable> {
  let player = GetPlayer(GetGameInstance());
  let targetingSystem = GameInstance.GetTargetingSystem(GetGameInstance());
  let spatialQueriesSystem = GameInstance.GetSpatialQueriesSystem(GetGameInstance());

  let aimPosition: Vector4;
  let aimForward: Vector4;
  targetingSystem.GetCrosshairData(player, aimPosition, aimForward);

  let endPosition = aimPosition + 100.0 * aimForward;
  let traceResult: TraceResult;
  spatialQueriesSystem.SyncRaycastByCollisionGroup(aimPosition, endPosition, n"Dynamic", traceResult, false, false);

  return TraceResult.GetHitObject(traceResult);
}
```

### Reference

- [DynamicEntitySystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/DynamicEntitySystem.reds)
- [DynamicEntitySpec](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/DynamicEntitySpec.reds)
- [DynamicEntityEvent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/DynamicEntityEvent.reds)
- [WeatherSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/WeatherSystem.reds)
- [WorldStateSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/WorldStateSystem.reds)
- [CommunityWrapper](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/CommunityWrapper.reds)
- [PopulationSpawnerWrapper](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/World/PopulationSpawnerWrapper.reds)

## Entities

### Entity template

You can get path to entity template used to create entity:

```swift
let player = GetPlayer(GetGameInstance());
let template = entity.GetTemplatePath();

FTLog(s"Entity Template: \(ResRef.GetHash(template))");
```

### Components

You can access entity components using new `GetComponents()` method:

```swift
let player = GetPlayer(GetGameInstance());
let components = player.GetComponents();

for component in components {
  FTLog(s"Component: \(component.GetName()) \(component.GetClassName())");
}
```

You can also add new components:

```swift
let comp = new entSkinnedMeshComponent();
comp.mesh *= r"mod\\player\\dynamic.mesh";
comp.meshApperance = n"default";

let player = GetPlayer(GetGameInstance());
player.AddComponent(comp);
```

To properly initialize components, you have to add components at the right moment, 
for example, when entity is assembled.

### Mesh appearances

After changing component mesh resource and/or appearance you can request it to load new appearance:

```swift
comp.mesh *= r"mod\\player\\dynamic.mesh";
comp.meshApperance = n"neon_red";
comp.LoadAppearance();
```

After changing any other properties that don't require loading resources you can refresh appearance: 

```swift
comp.RefreshAppearance();
```

Supported components:

- `entMeshComponent`
- `entSkinnedMeshComponent`
- `entGarmentSkinnedMeshComponent`
- `entMorphTargetSkinnedMeshComponent`

### Morph targets

You can set value (weight) for any morph target (shape key) defined in entity components.
For player, this includes all morph targets from customization and garment components.

```swift
let player = GetPlayer(GetGameInstance());
player.ApplyMorphTarget(n"h052", n"nose", 5.0);
```

### World transform

Static entities can be moved now without respawning them at new position:

```swift
entity.SetWorldTransform(transform);
```

### Reference

- [Entity](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Entity/Entity.reds)
- [IComponent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Entity/IComponent.reds)

## Player

### Accessing player objects

Besides the main player object, there are other player related puppets you may want to access.
With new functions added to player system you can access: 

- Customization screen puppet 
- Inventory screen puppet
- Photo mode puppet

```swift
let playerSystem = GameInstance.GetPlayerSystem(GetGameInstance());
let customizationPuppet = playerSystem.GetCustomizationPuppet();
let inventoryPuppet = playerSystem.GetInventoryPuppet();
let photoPuppet = playerSystem.GetPhotoPuppet();
```

### Managing wardrobe

Items can be permanently removed from wardrobe:

```swift
let wardrobeSystem = GameInstance.GetWardrobeSystem(GetGameInstance());
wardrobeSystem.ForgetItemID(ItemID.FromTDBID("Items.Glasses_03_basic_09"));
```

### Unlocking vehicles

Player vehicles can now be enabled by record ID instead of string, which normally can't be retrieved at runtime:

```swift
let vehicleSystem = GameInstance.GetVehicleSystem(GetGameInstance());
vehicleSystem.EnablePlayerVehicleID(t"Vehicle.v_sport2_quadra_type66_avenger_player", true);
```

### Reference

- [PlayerSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Player/PlayerSystem.reds)
- [VehicleSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Player/VehicleSystem.reds)
- [WardrobeSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Player/WardrobeSystem.reds)


## User Interface

### Layers and windows

All UI layers and windows can now be accessed, which gives direct access to all existing widgets, game and logic controllers.

```swift
let inkSystem = GameInstance.GetInkSystem();
let layers = inkSystem.GetLayers();

for layer in layers {
  FTLog(s"UI Layer: \(layer.GetLayerName()) \(layer.GetGameController().GetClassName())");
}
```

You can list all currently spawned game controllers:

```swift
let inkSystem = GameInstance.GetInkSystem();
let layers = inkSystem.GetLayers();

for layer in layers {
  for controller in layer.GetGameControllers() {
    FTLog(s"Game Controller: \(controller.GetClassName())");
  }
}
```

You can also access a layer directly by its name:

```swift
let inkSystem = GameInstance.GetInkSystem();
let hudRoot = inkSystem.GetLayer(n"inkHUDLayer").GetVirtualWindow();

let hello = new inkText();
hello.SetText("HELLO HUD");
hello.SetFontFamily("base\\gameplay\\gui\\fonts\\orbitron\\orbitron.inkfontfamily");
hello.SetFontStyle(n"Bold");
hello.SetFontSize(200);
hello.SetTintColor(new HDRColor(1.1761, 0.3809, 0.3476, 1.0));
hello.SetAnchor(inkEAnchor.Centered);
hello.SetAnchorPoint(0.5, 0.5);
hello.Reparent(hudRoot);
```

### Spawning widgets

When spawning widgets you can attach any custom game or logic controller on the fly.
If a library item defines controller, it will be overridden by your controller.
All controller properties set by the library item are inherited.

To override the controller you have to specify the controller class name next to the library item name:

```swift
let btn = this.SpawnFromLocal(parent, n"HyperlinkButton:MyButtonController");
```

When widget is spawning the controller will be overriden.

```swift
public class MyButtonController extends MenuItemController {
  protected cb func OnInitialize() -> Bool {
    super.OnInitialize();

    let data: MenuData;
    data.label = "My Button";
    data.icon = n"ico_deck_hub";

    this.Init(data);
  }
}
```

Controller overrides also work inside `.inkwidget` library.
When a widget requires a library item, for example, `inkVirtualGridController`, 
you can also insert the controller into the library item name: `itemDisplay` → `itemDisplay:MyMod.MyController`.

### Scripted widgets

Widgets and controllers created from scripts are now attached to all game systems and fully functional.
You can initialize any native controller, e.g. `inkScrollController`, or create your own.

The new `inkComponent` class allows you to define the widget and logic as one unit:

```swift
public class MyComponent extends inkComponent {
  // Called when component is created
  // Must return the root widget of the component
  protected cb func OnCreate() -> ref<inkWidget> {
    let root = new inkRectangle();
    root.SetAnchor(inkEAnchor.Fill);
    root.SetOpacity(1.0);

    return root;
  }

  // Called when component is attached to the widget tree
  protected cb func OnInitialize() {}

  // Called when component is no longer used anywhere
  protected cb func OnUninitialize() {}
  
  public func SetColor(color: HDRColor) {
    this.GetRootWidget().SetTintColor(color);
  }
}
```

Then it can be added to an existing widget tree:

```swift
let comp = new MyComponent();
comp.SetColor(new HDRColor(1.1761, 0.3809, 0.3476, 1.0));
comp.Reparent(parent);
```

> **Backwards compatibility**  
> Existing mods can keep using `inkCustomController` without changes.   

### UI Framework

Codeware includes ready-to-use components for buttons, action hints, text inputs, popups.
For examples of use, see the following mods:

- [Ink Playground](https://github.com/psiberx/cp2077-playground)
- [Stealthrunner](https://www.nexusmods.com/cyberpunk2077/mods/7616)
- [Equipment-EX](https://github.com/psiberx/cp2077-equipment-ex)

### Reference

- [inkSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/UI/inkSystem.reds)
- [inkComponent](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/UI/Core/inkComponent.reds)

## Resources

### Resource references

Resource references (`rRef` and `raRef`) can now be imported and manipulated from scripts.

```swift
@addField(WeaponObject)
public native let effect: ResourceRef;

@addField(inkMask)
public native let textureAtlas: ResourceAsyncRef;
```

Reference can be initialized by assigning a resource path using `*=` operator:

```swift
let weapon = new WeaponObject();
weapon.effect *= r"base\\gameplay\\game_effects\\strongmelee.es";

FTLog(s"Hash: \(ResourceRef.GetHash(weapon.effect))");
FTLog(s"Loaded: \(ResourceRef.IsLoaded(weapon.effect))");
```

### Checking resource existence

With basic depot access, you can check if any particular archive (legacy and redmod) or resource is present in the game. 

For example, you can use to check if mod is intalled correctly:

```swift
let depot = GameInstance.GetResourceDepot();
if !depot.ArchiveExists("MyMod.archive") {
  FTLog("MyMod.archive not found. Did you enable mods?");
}
```

Or to handle compatibility with another mod:

```swift
let depot = GameInstance.GetResourceDepot();
if depot.ResourceExists(r"mod\\entities\\vehicle.ent") {
  FTLog("Another mod detected");
}
```

### Reading resources

```swift
class MySystem extends ScriptableSystem {
  private func OnAttach() {
    let token = GameInstance.GetResourceDepot()
      .LoadResource(r"base\\vehicles\\standard\\v_standard3_thorton_mackinaw_01__basic_01.ent");
    token.RegisterCallback(this, n"OnResourceReady");
  }

  private cb func OnResourceReady(token: ref<ResourceToken>) {
    let template = token.GetResource() as entEntityTemplate;

    FTLog("Available appearances:");

    for appearance in template.appearances {
      FTLog(s"- \(appearance.name)");
    }
  }
}
```

### Reference

- [ResourceDepot](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Depot/ResourceDepot.reds)
- [ResourceReference](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Depot/ResourceReference.reds)
- [ResourceToken](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Depot/ResourceToken.reds)

## Localization

### Localization system

The localization system provides a script approach to add translations and allows you to:

- Automatically apply translations based on the game language settings
- Use different language packages for interface and subtitles 
- Vary translations based on player gender

Texts from localization providers are registered in native localization system as well,
so they can be used with `GetLocalizedTextByKey`/`GetLocalizedText` functions and in TweakDB.

```swift
module MyMod.UI
import Codeware.UI.*

public class MyModWidget extends inkCustomController {
  private let m_title: ref<inkText>;
  private let m_action: ref<inkText>;

  private cb func OnInitialize() -> Void {
    this.m_title.SetText(GetLocalizedTextByKey(n"MyMod-Title"));
    this.m_action.SetText(GetLocalizedTextByKey(n"MyMod-Action-Use"));
  }
}
```

### Localization providers

First, you need to define a localization provider. 
The main purpose of the provider is to resolve packages by language code and define fallback language:

```swift
module MyMod.Localization
import Codeware.Localization.*

public class LocalizationProvider extends ModLocalizationProvider {
  public func GetPackage(language: CName) -> ref<ModLocalizationPackage> {
    switch language {
      case n"en-us": return new English();
      case n"de-de": return new German();
      case n"it-it": return new Italian();
      default: return null;
    }
  }

  public func GetFallback() -> CName {
    return n"en-us";
  }
}
```

Provider can also track language changes and notify other components:

```swift
public class LocalizationProvider extends ModLocalizationProvider {
  public func OnLocaleChange() -> Void {
    // Notify other components, clear cache, ...
  }
}
```

### Localization packages

Second, you define localization packages that contain translations for a specific language: 

```swift
module MyMod.Localization
import Codeware.Localization.*

public class English extends ModLocalizationPackage {
  protected func DefineTexts() -> Void {
    this.Text("MyMod-Title", "Best Mod");
    this.Text("MyMod-Action-Use", "Do It");

    // To define gender specific translations:
    this.TextM("MyMod-Greeting", "Hey Boy");
    this.TextF("MyMod-Greeting", "Hey Girl");
        
    // Alternatively it can be one statement:
    this.Text("MyMod-Greeting", "Hey Girl", "Hey Boy");
  }

  protected func DefineSubtitles() -> Void {
    // this.Subtitle(...);
    // this.SubtitleM(...);
    // this.SubtitleF(...);
  }
}
```

### Third-party translations

Translations can also be provided by mod users in the form of another mod:

```swift
module MyMod_Chinese
import Codeware.Localization.*

public class LocalizationProvider extends ModLocalizationProvider {
  public func GetPackage(language: CName) -> ref<ModLocalizationPackage> {
    return Equals(language, n"zh-cn") ? new LocalizationPackage() : null;
  }
}

public class LocalizationPackage extends ModLocalizationPackage {
  protected func DefineTexts() -> Void {
    this.Text("MyMod-Title", "最佳模组");
    this.Text("MyMod-Action-Use", "做吧");
  }
}
```

### Reference

- [LocalizationSystem](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Localization/LocalizationSystem.reds)
- [ModLocalizationProvider](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Localization/Module/ModLocalizationProvider.reds)
- [ModLocalizationPackage](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Localization/Module/ModLocalizationPackage.reds)

## Reflection

### Inspecting types and values

You can get various type information using type name or variable:

```swift
let cls = Reflection.GetClass(n"inkWidget");

if cls.IsNative() {
  FTLog(s"\(cls.GetName()) is native class");
}

for prop in cls.GetProperties() {
  FTLog(s"\(prop.GetName()): \(prop.GetType().GetName())");
}
```

You can also access properties and call methods:

```swift
let image = new inkImage();
image.SetTexturePart(n"foo");

let imageRef = Reflection.GetTypeOf(image); // Resolves to ref<inkImage>
let imageClass = imageRef.GetInnerType().AsClass(); // Get to inkImage class

let prop = imageClass.GetProperty(n"texturePart");
let getter = imageClass.GetFunction(n"GetTexturePart");
let setter = imageClass.GetFunction(n"SetTexturePart");

let val1 = prop.GetValue(image); // Read property from instance
let val2 = getter.Call(image); // Call getter on instance

FTLog(s"Expected type: \(prop.GetType().GetName())");
FTLog(s"Value from property: \(FromVariant<CName>(val1))");
FTLog(s"Value from getter: \(FromVariant<CName>(val2))");

setter.Call(image, [n"bar"]); // Change the value using setter 

FTLog(s"New value: \(image.GetTexturePart())");
```

### Custom callbacks

You can implement your own callbacks similar to game native callbacks:

```swift
struct MyCallback {
  let target: wref<IScriptable>;
  let function: CName;
}

class MyService {
  private let callbacks: array<MyCallback>;

  public func RegisterCallback(target: ref<IScriptable>, function: CName) {
    ArrayPush(this.callbacks, new MyCallback(target, function));
  }
  
  public func FireCallbacks(data: ref<IScriptable>) {
    for callback in this.callbacks {
      if IsDefined(callback.target) {
        Reflection.GetClassOf(callback.target)
          .GetFunction(callback.function)
          .Call(callback.target, [data]);
      }
    }
  }
}
```

You can also handle call status and return value:

```swift
class MyService {
  public func FireCallback(target: ref<IScriptable>, function: CName, data: ref<IScriptable>) {
    let type = Reflection.GetClassOf(target);
    let callable = type.GetFunction(function);
    
    if IsDefined(callable) {
      let status = false;
      let result = callable.Call(target, [data], status);
      
      if status {
        FTLog(s"Result: \(VariantTypeName(result))");
      } else {
        FTLog(s"Method \(type.GetName()).\(function) must accept one parameter");
      }
    } else {
      FTLog(s"Method \(type.GetName()).\(function) not found");
    }
  }
}
```

Don't forget to use `cb` modifier for callbacks to be able to use functions short names. 

```swift
class MyHandler {
  protected cb func Callback(data: ref<IScriptable>) {
    FTLog(s"It's working! Received \(data.GetClassName()).");
  }
}

let handler = new MyHandler();
let service = new MyService();
service.RegisterCallback(handler, n"Callback");
service.FireCallbacks(new GameObject());
```

### Mods and patches compatibility

In cases where you can't use conditional compilation with `ModuleExists()`, 
you can use reflection to check if a particular class, property or function exists, 
apply different logic and access it safely.

### Reference

- [Reflection](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/Reflection.reds)
- [ReflectionType](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ReflectionType.reds)
- [ReflectionEnum](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ReflectionEnum.reds)
- [ReflectionClass](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ReflectionClass.reds)
- [ReflectionProp](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ReflectionProp.reds)
- [ReflectionFunc](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ReflectionFunc.reds)
- [ERTTIType](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Reflection/ERTTIType.reds)

## Utilities

### CName

```swift
let name = n"test";
let hash = NameToHash(name);

FTLog(s"Name: \(name) -> Hash: \(hash)");
```

### NodeRef

```swift
let nodeRef = ToNodeRef("$/my/new/#node");

FTLog(s"NodeRef: \(NodeRefToHash(nodeRef))");
```

### CRUID

```swift
let id = ToCRUID(1337ul);

FTLog(s"CRUID: \(CRUIDToHash(id))");
```

### Hash functions

```swift
let hash1: Uint64 = FNV1a64("data");
let hash2: Uint32 = FNV1a32("data");
let hash3: Uint32 = Murmur3("data");
```

### Bitwise operations

```swift
let mask1: Uint64 = BitSet64(0, 4, true);
let mask2: Uint16 = BitShiftL16(1, 3);
let test: Bool = BitTest32(6, 1);
```

### Reference

- [CName](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/CName.reds)
- [CRUID](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/CRUID.reds)
- [NodeRef](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/NodeRef.reds)
- [String](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/String.reds)
- [Hash](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/Hash.reds)
- [Bits](https://github.com/psiberx/cp2077-codeware/blob/main/scripts/Utils/Bits.reds)
