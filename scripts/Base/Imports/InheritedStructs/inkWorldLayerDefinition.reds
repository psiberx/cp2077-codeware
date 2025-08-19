public native struct inkWorldLayerDefinition {
  public native let enabled: Bool;
  public native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let activeByDefault: Bool;
  public native let isPermanent: Bool;
  public native let useGlobalStyleTheme: Bool;
  public native let isAffectedByFadeout: Bool;
  public native let useGameInput: Bool;
  public native let inputContext: CName;
  public native let projectionPlaneSize: Vector2;
  public native let renderingPlane: ERenderingPlane;
  public native let isAlwaysVisible: Bool;
  public native let isInteractableFromBehind: Bool;
  public native let maxInteractionDistance: Float;
  public native let overrideMaxInteractionDistance: Bool;
  public native let useCustomFaceVector: Bool;
  public native let faceVector: Vector3;
}
