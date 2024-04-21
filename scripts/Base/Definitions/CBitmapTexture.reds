public native class CBitmapTexture extends ITexture {
  native let width: Uint32;
  native let height: Uint32;
  native let depth: Uint32;
  native let setup: STextureGroupSetup;
  native let histBiasMulCoef: Vector3;
  native let histBiasAddCoef: Vector3;
  native let renderTextureResource: rendRenderTextureResource;
}
