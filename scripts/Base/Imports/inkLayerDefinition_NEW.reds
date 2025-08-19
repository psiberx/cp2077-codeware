public native struct inkLayerDefinition_NEW {
  public native let name: CName;
  public native let layerType: inkELayerType;
  public native let drawingPolicy: inkLayerDrawingPolicy;
  public native let loadPriority: inkELayerLoadPriority;
  public native let enabled: Bool;
  public native let isPermanent: Bool;
  public native let useGlobalStyleTheme: Bool;
  public native let isAffectedByFadeout: Bool;
  public native let useGameInput: Bool;
  public native let inputContext: CName;
}
