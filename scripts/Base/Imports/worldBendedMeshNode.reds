public native class worldBendedMeshNode extends worldNode {
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
  native let meshAppearance: CName;
  native let deformationData: array<Matrix>;
  native let deformedBox: Box;
  native let isBendedRoad: Bool;
  native let castShadows: shadowsShadowCastingMode;
  native let castLocalShadows: shadowsShadowCastingMode;
  native let removeFromRainMap: Bool;
  native let navigationSetting: NavGenNavigationSetting;
  native let version: Uint8;
}
