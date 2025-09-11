public native struct gameuiExternalPhoneElement {
  public native let libraryID: CName;
  public native let request: wref<inkAsyncSpawnRequest>;
  public native let widget: wref<inkWidget>;
  public native let tierVisibility: Uint64; // worlduiContextVisibility
  public native let gameContextVisibility: Uint32; // gameuiContext
  public native let slot: inkCompoundRef;
  public native let libraryResource: ResourceRef; // rRef<inkWidgetLibraryResource>
}
