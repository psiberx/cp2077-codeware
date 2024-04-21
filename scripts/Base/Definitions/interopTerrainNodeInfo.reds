public native struct interopTerrainNodeInfo {
  native let width: Uint32;
  native let height: Uint32;
  native let externalDataSource: Bool;
  native let isTerrainNode: Bool;
  native let blendOrder: Uint8;
  native let blendModeHeightIsIgnore: Bool;
  native let blendModeHeightIsNormal: Bool;
  native let blendModeColorIsIgnore: Bool;
  native let blendModeHolesIsIgnore: Bool;
  native let terrainSysID: Uint16;
  native let nodeName: String;
  native let nodeScale: Vector3;
  native let nodeTransform: Transform;
  native let nodeCellResScale: Float;
  native let densityTexelSize: Float;
  native let nodeIDPath: toolsEditorObjectIDPath;
}
