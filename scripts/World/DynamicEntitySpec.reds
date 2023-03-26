
public native class DynamicEntitySpec {
    public native let recordID: TweakDBID;
    public native let templatePath: ResRef;
    public native let appearanceName: CName;
    public native let position: Vector4;
    public native let orientation: Quaternion;
    public native let persistState: Bool;
    public native let persistSpawn: Bool;
    public native let alwaysSpawned: Bool;
    public native let spawnInView: Bool;
    public native let tags: array<CName>;
    public native let active: Bool;

    public native func IsValid() -> Bool
}
