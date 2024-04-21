public native struct rendRenderMultilayerMaskBlobHeader {
  native let version: Uint32;
  native let atlasWidth: Uint32;
  native let atlasHeight: Uint32;
  native let numLayers: Uint32;
  native let maskWidth: Uint32;
  native let maskHeight: Uint32;
  native let maskWidthLow: Uint32;
  native let maskHeightLow: Uint32;
  native let maskTileSize: Uint32;
  native let flags: Uint32;
}
