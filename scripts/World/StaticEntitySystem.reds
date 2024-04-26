public native class StaticEntitySystem extends IGameSystem {
    public native func IsReady() -> Bool

    public native func SpawnEntity(spec: ref<StaticEntitySpec>) -> EntityID
    public native func DespawnEntity(id: EntityID) -> Bool
    public native func AttachEntity(id: EntityID) -> Bool
    public native func DetachEntity(id: EntityID) -> Bool

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
    public native func DespawnTagged(tag: CName)
    public native func AttachTagged(tag: CName)
    public native func DetachTagged(tag: CName)
}

@addMethod(GameInstance)
public static native func GetStaticEntitySystem() -> ref<StaticEntitySystem>
