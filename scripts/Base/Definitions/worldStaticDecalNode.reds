public native class worldStaticDecalNode extends worldNode {
  native let material: ResourceAsyncRef; // raRef<IMaterial>
  native let autoHideDistance: Float;
  native let verticalFlip: Bool;
  native let horizontalFlip: Bool;
  native let alpha: Float;
  native let normalThreshold: Float;
  native let roughnessScale: Float;
  native let diffuseColorScale: HDRColor;
  native let isStretchingEnabled: Bool;
  native let enableNormalTreshold: Bool;
  native let orderNo: Uint16;
  native let surfaceType: ERenderObjectType;
  native let normalsBlendingMode: RenderDecalNormalsBlendingMode;
  native let decalRenderMode: EDecalRenderMode;
  native let shouldCollectWithRayTracing: Bool;
  native let forcedAutoHideDistance: Float;
  native let decalNodeVersion: Uint8;
}
