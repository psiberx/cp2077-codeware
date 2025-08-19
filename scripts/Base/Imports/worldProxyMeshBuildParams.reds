public native struct worldProxyMeshBuildParams {
  public native let buildProxy: Bool;
  public native let type: worldProxyMeshBuildType;
  public native let usedMesh: worldProxyMeshOutputType;
  public native let resolution: Uint32;
  public native let polycount: Uint32;
  public native let polycountPercentage: Float;
  public native let coreAxis: worldProxyCoreAxis;
  public native let groupingNormals: worldProxyGroupingNormals;
  public native let forceSurfaceFlattening: Bool;
  public native let forceSeamlessModule: Bool;
  public native let enableAlphaMask: Bool;
  public native let windows: worldProxyWindowsParams;
  public native let textures: worldProxyTextureParams;
  public native let customGeometry: worldProxyCustomGeometryParams;
  public native let advancedParams: worldProxyMeshAdvancedBuildParams;
}
