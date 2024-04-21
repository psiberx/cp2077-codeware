public native struct inkMenuEntry {
  native let name: CName;
  native let menuWidget: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let depth: Uint32;
  native let spawnMode: inkSpawnMode;
  native let isAffectedByFadeout: Bool;
  native let inputContext: CName;
}
