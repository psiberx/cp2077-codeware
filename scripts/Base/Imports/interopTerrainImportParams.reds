public native struct interopTerrainImportParams {
  public native let cellRes: Uint32;
  public native let cellSize: Uint32;
  public native let scale: Vector3;
  public native let position: Vector3;
  public native let extraOffset: Vector2;
  public native let tileWidth: Uint32;
  public native let tileHeight: Uint32;
  public native let prefabPlacementInterval: Uint32;
  public native let importHeightMaps: Bool;
  public native let importColorMaps: Bool;
  public native let importControlMaps: Bool;
  public native let overwriteTransformsOfExistingNodes: Bool;
  public native let nodesNamingPattern: String;
  public native let prefabsNamingPattern: String;
  public native let prefabsDestinationPath: String;
  public native let dstPrefabNodePath: toolsEditorObjectIDPath;
}
