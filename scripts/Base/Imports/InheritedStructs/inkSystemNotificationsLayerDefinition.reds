public native struct inkSystemNotificationsLayerDefinition {
  native let enabled: Bool;
  native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let activeByDefault: Bool;
  native let isPermanent: Bool;
  native let useGlobalStyleTheme: Bool;
  native let isAffectedByFadeout: Bool;
  native let useGameInput: Bool;
  native let inputContext: CName;

  native let cursorResource: ResourceRef; // rRef<inkWidgetLibraryResource>
}
