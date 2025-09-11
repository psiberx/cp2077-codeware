public native class worldBakedDestructionNode extends worldMeshNode {
  public native let meshFractured: ResourceAsyncRef; // raRef<CMesh>
  public native let meshFracturedAppearance: CName;
  public native let numFrames: Float;
  public native let frameRate: Float;
  public native let playOnlyOnce: Bool;
  public native let restartOnTrigger: Bool;
  public native let disableCollidersOnTrigger: Bool;
  public native let filterDataSource: physicsFilterDataSource;
  public native let filterData: ref<physicsFilterData>;
  public native let damageThreshold: Float;
  public native let damageEndurance: Float;
  public native let impulseToDamage: Float;
  public native let contactToDamage: Float;
  public native let accumulateDamage: Bool;
  public native let fractureFieldMask: Uint16; // physicsFractureFieldType
  public native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let audioMetadata: CName;
  public native let navigationSetting: NavGenNavigationSetting;
  public native let useMeshNavmeshSettings: Bool;
}
