public native class PhysicalDestructionNode extends worldNode {
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let meshAppearance: CName;
  public native let forceLODLevel: Int32;
  public native let forceAutoHideDistance: Float;
  public native let destructionParams: physicsDestructionParams;
  public native let destructionLevelData: array<physicsDestructionLevelData>;
  public native let audioMetadata: CName;
  public native let navigationSetting: NavGenNavigationSetting;
  public native let useMeshNavmeshSettings: Bool;
  public native let systemsToNotifyFlags: Uint16;
}
