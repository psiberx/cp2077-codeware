public native class worldMeshNode extends worldNode {
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
  native let meshAppearance: CName;
  native let forceAutoHideDistance: Float;
  native let occluderType: visWorldOccluderType;
  native let occluderAutohideDistanceScale: Uint8;
  native let castShadows: shadowsShadowCastingMode;
  native let castLocalShadows: shadowsShadowCastingMode;
  native let castRayTracedGlobalShadows: shadowsShadowCastingMode;
  native let castRayTracedLocalShadows: shadowsShadowCastingMode;
  native let windImpulseEnabled: Bool;
  native let removeFromRainMap: Bool;
  native let lodLevelScales: Uint32;
  native let version: Uint8;
}
