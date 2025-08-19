public native class worldInstancedMeshNode extends worldNode {
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let meshAppearance: CName;
  public native let castShadows: shadowsShadowCastingMode;
  public native let castLocalShadows: shadowsShadowCastingMode;
  public native let occluderType: visWorldOccluderType;
  public native let meshLODScales: Uint32;
  public native let occluderAutohideDistanceScale: Uint8;
  public native let worldTransformsBuffer: worldRenderProxyTransformBuffer;
  public native let version: Uint8;
}
