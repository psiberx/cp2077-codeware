public native struct worldProxyTextureParams {
  native let exportVertexColor: Bool;
  native let albedoTextureResolution: worldProxyMeshTexRes;
  native let generateAlbedo: Bool;
  native let normalTextureResolution: worldProxyMeshTexRes;
  native let generateNormal: Bool;
  native let roughnessTextureResolution: worldProxyMeshTexRes;
  native let generateRoughness: Bool;
  native let metalnessTextureResolution: worldProxyMeshTexRes;
  native let generateMetalness: Bool;
  native let disableTextureFilter: Bool;
  native let diffuseAlphaAsEmissive: Bool;
}
