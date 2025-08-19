public native struct inkMenuEntry {
  public native let name: CName;
  public native let menuWidget: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let depth: Uint32;
  public native let spawnMode: inkSpawnMode;
  public native let isAffectedByFadeout: Bool;
  public native let inputContext: CName;
}
