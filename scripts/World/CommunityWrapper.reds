public native class CommunityEntryWrapper {
    public native func IsActive() -> Bool
    public native func GetName() -> CName
    public native func GetPhases() -> array<CName>
    public native func GetRestoredEntityIDs() -> array<EntityID>
    public native func GetSpawnedEntityIDs() -> array<EntityID>
    public native func GetSpawningEntityIDs() -> array<EntityID>
    public native func GetReservedEntityIDs() -> array<EntityID>
    public native func GetTemplateEntryData() -> ref<communitySpawnEntry>
}

public native class CommunityWrapper {
    public native func GetEntries() -> array<ref<CommunityEntryWrapper>>
    public native func GetActiveEntityIDs() -> array<EntityID>
    public native func GetTemplateData() -> ref<communityCommunityTemplateData>
}