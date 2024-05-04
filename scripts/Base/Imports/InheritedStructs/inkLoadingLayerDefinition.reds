public native struct inkLoadingLayerDefinition {
  native let enabled: Bool;
  native let rootLibrary: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let activeByDefault: Bool;
  native let isPermanent: Bool;
  native let useGlobalStyleTheme: Bool;
  native let isAffectedByFadeout: Bool;
  native let useGameInput: Bool;
  native let inputContext: CName;

  native let splashLoadingScreenResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  native let initialLoadingScreenResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  native let fastTravelLoadingScreenResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  native let fallbackLoadingScreenResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
}
