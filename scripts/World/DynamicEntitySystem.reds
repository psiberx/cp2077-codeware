public native class DynamicEntitySystem extends IGameSystem {
    public native func IsReady() -> Bool
    public native func IsRestored() -> Bool

    public native func CreateEntity(spec: ref<DynamicEntitySpec>) -> EntityID
    public native func DeleteEntity(id: EntityID) -> Bool
    public native func EnableEntity(id: EntityID) -> Bool
    public native func DisableEntity(id: EntityID) -> Bool

    public native func IsManaged(id: EntityID) -> Bool
    public native func IsTagged(id: EntityID, tag: CName) -> Bool
    public native func IsSpawned(id: EntityID) -> Bool
    public native func IsSpawning(id: EntityID) -> Bool
    public native func GetEntity(id: EntityID) -> ref<Entity>
    public native func GetTags(id: EntityID) -> array<CName>
    public native func AssignTag(id: EntityID, tag: CName)
    public native func UnassignTag(id: EntityID, tag: CName)

    public native func IsPopulated(tag: CName) -> Bool
    public native func GetTagged(tag: CName) -> array<ref<Entity>>
    public native func GetTaggedID(tag: CName) -> EntityID
    public native func GetTaggedIDs(tag: CName) -> array<EntityID>
    public native func DeleteTagged(tag: CName)
    public native func EnableTagged(tag: CName)
    public native func DisableTagged(tag: CName)

    public native func RegisterListener(tag: CName, target: ref<IScriptable>, function: CName)
    public native func UnregisterListener(tag: CName, target: ref<IScriptable>, function: CName)
    public native func UnregisterListeners(tag: CName)
}

@addMethod(GameInstance)
public static native func GetDynamicEntitySystem() -> ref<DynamicEntitySystem>
