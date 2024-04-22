public native struct inkLayerDefinition_NEW {
  native let name: CName;
  native let layerType: inkELayerType;
  native let drawingPolicy: inkLayerDrawingPolicy;
  native let loadPriority: inkELayerLoadPriority;
  native let enabled: Bool;
  native let isPermanent: Bool;
  native let useGlobalStyleTheme: Bool;
  native let isAffectedByFadeout: Bool;
  native let useGameInput: Bool;
  native let inputContext: CName;
}
