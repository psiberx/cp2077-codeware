public native class PopulationSpawnerWrapper {
    public native func IsActive() -> Bool
    public native func IsInitialized() -> Bool
    public native func GetRecordID() -> TweakDBID
    public native func GetAppearanceName() -> CName
    public native func GetTransform() -> WorldTransform
    public native func GetActiveEntityIDs() -> array<EntityID>
    public native func GetRestoredEntityIDs() -> array<EntityID>
    public native func GetSpawnedEntityIDs() -> array<EntityID>
    public native func GetReservedEntityIDs() -> array<EntityID>
}
