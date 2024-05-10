public native struct inkWaitingSignLayerDefinition {
  native let enabled: Bool;
  native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let activeByDefault: Bool;
  native let isPermanent: Bool;
  native let useGlobalStyleTheme: Bool;
  native let isAffectedByFadeout: Bool;
  native let useGameInput: Bool;
  native let inputContext: CName;
  native let introAnimName: CName;
  native let waitingAnimName: CName;
  native let outroAnimName: CName;
  native let delayTime: Float;
  native let introTime: Float;
  native let waitingTime: Float;
  native let postWaitTime: Float;
  native let outroTime: Float;
}
