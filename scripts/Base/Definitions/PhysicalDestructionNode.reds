public native class PhysicalDestructionNode extends worldNode {
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
  native let meshAppearance: CName;
  native let forceLODLevel: Int32;
  native let forceAutoHideDistance: Float;
  native let destructionParams: physicsDestructionParams;
  native let destructionLevelData: array<physicsDestructionLevelData>;
  native let audioMetadata: CName;
  native let navigationSetting: NavGenNavigationSetting;
  native let useMeshNavmeshSettings: Bool;
  native let systemsToNotifyFlags: Uint16;
}
