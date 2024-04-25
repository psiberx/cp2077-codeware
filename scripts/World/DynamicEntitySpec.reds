public native class DynamicEntitySpec {
    // The entity record or template to spawn. Can't be used together.
    public native let recordID: TweakDBID;
    public native let templatePath: ResRef;

    // Initial appearance name. If not set, default apperance will be used.
    public native let appearanceName: CName;

    // Initial spawn position and orientation.
    public native let position: Vector4;
    public native let orientation: Quaternion;

    // Should entity state (position, inventory, health, etc.) be saved and restored on next spawn.
    public native let persistState: Bool;

    // Should entity be saved and restored next time this playthrough is loaded.
    public native let persistSpawn: Bool;

    // Should entity be always spawned or only when player is around.
    public native let alwaysSpawned: Bool;

    // Should entity spawn when player sees spawn position, or wait until player will look away.
    public native let spawnInView: Bool;

    // Should entity spawn on creation or just register in the system.
    public native let active: Bool;

    // Initital tags associated with the entity.
    public native let tags: array<CName>;
}
