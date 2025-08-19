public native struct worldProxyTextureParams {
  public native let exportVertexColor: Bool;
  public native let albedoTextureResolution: worldProxyMeshTexRes;
  public native let generateAlbedo: Bool;
  public native let normalTextureResolution: worldProxyMeshTexRes;
  public native let generateNormal: Bool;
  public native let roughnessTextureResolution: worldProxyMeshTexRes;
  public native let generateRoughness: Bool;
  public native let metalnessTextureResolution: worldProxyMeshTexRes;
  public native let generateMetalness: Bool;
  public native let disableTextureFilter: Bool;
  public native let diffuseAlphaAsEmissive: Bool;
}
