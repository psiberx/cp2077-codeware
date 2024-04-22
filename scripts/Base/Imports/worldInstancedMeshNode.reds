public native class worldInstancedMeshNode extends worldNode {
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
  native let meshAppearance: CName;
  native let castShadows: shadowsShadowCastingMode;
  native let castLocalShadows: shadowsShadowCastingMode;
  native let occluderType: visWorldOccluderType;
  native let meshLODScales: Uint32;
  native let occluderAutohideDistanceScale: Uint8;
  native let worldTransformsBuffer: worldRenderProxyTransformBuffer;
  native let version: Uint8;
}
