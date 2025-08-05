public enum DynamicEntityEventType
{
    Created = 0,
    Deleted = 1,
    Spawned = 2,
    Despawned = 3,
    Dead = 4,
}

public native class DynamicEntityEvent {
    public native func GetEventType() -> DynamicEntityEventType
    public native func GetEntityID() -> EntityID
    public native func GetEntityTag() -> CName
}
