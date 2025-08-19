public native class CBitmapTexture extends ITexture {
  public native let width: Uint32;
  public native let height: Uint32;
  public native let depth: Uint32;
  public native let setup: STextureGroupSetup;
  public native let histBiasMulCoef: Vector3;
  public native let histBiasAddCoef: Vector3;
  public native let renderResourceBlob: ref<IRenderResourceBlob>;
  public native let renderTextureResource: rendRenderTextureResource;
}
