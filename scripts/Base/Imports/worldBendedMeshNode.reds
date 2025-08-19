public native class worldBendedMeshNode extends worldNode {
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let meshAppearance: CName;
  public native let deformationData: array<Matrix>;
  public native let deformedBox: Box;
  public native let isBendedRoad: Bool;
  public native let castShadows: shadowsShadowCastingMode;
  public native let castLocalShadows: shadowsShadowCastingMode;
  public native let removeFromRainMap: Bool;
  public native let navigationSetting: NavGenNavigationSetting;
  public native let version: Uint8;
}
