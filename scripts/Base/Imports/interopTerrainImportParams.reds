public native struct interopTerrainImportParams {
  native let cellRes: Uint32;
  native let cellSize: Uint32;
  native let scale: Vector3;
  native let position: Vector3;
  native let extraOffset: Vector2;
  native let tileWidth: Uint32;
  native let tileHeight: Uint32;
  native let prefabPlacementInterval: Uint32;
  native let importHeightMaps: Bool;
  native let importColorMaps: Bool;
  native let importControlMaps: Bool;
  native let overwriteTransformsOfExistingNodes: Bool;
  native let nodesNamingPattern: String;
  native let prefabsNamingPattern: String;
  native let prefabsDestinationPath: String;
  native let dstPrefabNodePath: toolsEditorObjectIDPath;
}
