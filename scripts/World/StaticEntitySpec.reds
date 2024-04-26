public native class StaticEntitySpec {
    // The entity template to spawn.
    public native let templatePath: ResRef;

    // Initial appearance name. If not set, default apperance will be used.
    public native let appearanceName: CName;

    // Initial spawn position and orientation.
    public native let position: Vector4;
    public native let orientation: Quaternion;

    // Should entity be attached after spawn or stay detached.
    public native let attached: Bool;

    // Initital tags associated with the entity.
    public native let tags: array<CName>;
}
