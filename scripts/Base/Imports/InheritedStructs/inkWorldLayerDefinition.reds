public native struct inkWorldLayerDefinition {
  native let enabled: Bool;
  native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let activeByDefault: Bool;
  native let isPermanent: Bool;
  native let useGlobalStyleTheme: Bool;
  native let isAffectedByFadeout: Bool;
  native let useGameInput: Bool;
  native let inputContext: CName;
  native let projectionPlaneSize: Vector2;
  native let renderingPlane: ERenderingPlane;
  native let isAlwaysVisible: Bool;
  native let isInteractableFromBehind: Bool;
  native let maxInteractionDistance: Float;
  native let overrideMaxInteractionDistance: Bool;
  native let useCustomFaceVector: Bool;
  native let faceVector: Vector3;
}
