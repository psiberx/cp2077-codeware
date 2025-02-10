@neverRef() public native class CCubeTexture extends ITexture {
  native let setup: STextureGroupSetup;
  native let size: Uint32;
  native let renderResourceBlob: ref<IRenderResourceBlob>;
  native let renderTextureResource: rendRenderTextureResource;
}

