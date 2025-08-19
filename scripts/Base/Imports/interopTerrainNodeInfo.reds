public native struct interopTerrainNodeInfo {
  public native let width: Uint32;
  public native let height: Uint32;
  public native let externalDataSource: Bool;
  public native let isTerrainNode: Bool;
  public native let blendOrder: Uint8;
  public native let blendModeHeightIsIgnore: Bool;
  public native let blendModeHeightIsNormal: Bool;
  public native let blendModeColorIsIgnore: Bool;
  public native let blendModeHolesIsIgnore: Bool;
  public native let terrainSysID: Uint16;
  public native let nodeName: String;
  public native let nodeScale: Vector3;
  public native let nodeTransform: Transform;
  public native let nodeCellResScale: Float;
  public native let densityTexelSize: Float;
  public native let nodeIDPath: toolsEditorObjectIDPath;
}
