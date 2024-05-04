public native struct worldGroupProxyMeshBuildParams {
  native let buildProxy: Bool;
  native let type: worldProxyMeshBuildType;
  native let usedMesh: worldProxyMeshOutputType;
  native let resolution: Uint32;
  native let polycount: Uint32;
  native let polycountPercentage: Float;
  native let coreAxis: worldProxyCoreAxis;
  native let groupingNormals: worldProxyGroupingNormals;
  native let forceSurfaceFlattening: Bool;
  native let forceSeamlessModule: Bool;
  native let enableAlphaMask: Bool;
  native let windows: worldProxyWindowsParams;
  native let textures: worldProxyTextureParams;
  native let customGeometry: worldProxyCustomGeometryParams;
  native let advancedParams: worldProxyMeshAdvancedBuildParams;
}
