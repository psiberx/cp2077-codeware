public native struct inkWaitingSignLayerDefinition {
  public native let enabled: Bool;
  public native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let activeByDefault: Bool;
  public native let isPermanent: Bool;
  public native let useGlobalStyleTheme: Bool;
  public native let isAffectedByFadeout: Bool;
  public native let useGameInput: Bool;
  public native let inputContext: CName;
  public native let introAnimName: CName;
  public native let waitingAnimName: CName;
  public native let outroAnimName: CName;
  public native let delayTime: Float;
  public native let introTime: Float;
  public native let waitingTime: Float;
  public native let postWaitTime: Float;
  public native let outroTime: Float;
}
