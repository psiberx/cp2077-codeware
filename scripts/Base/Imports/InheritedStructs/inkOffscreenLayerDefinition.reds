public native struct inkOffscreenLayerDefinition {
  public native let enabled: Bool;
  public native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let activeByDefault: Bool;
  public native let isPermanent: Bool;
  public native let useGlobalStyleTheme: Bool;
  public native let isAffectedByFadeout: Bool;
  public native let useGameInput: Bool;
  public native let inputContext: CName;
}
