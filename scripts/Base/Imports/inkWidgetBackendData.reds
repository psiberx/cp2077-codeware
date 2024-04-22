public native class inkWidgetBackendData extends IBackendData {
  native let owner: wref<inkWidget>;
  native let isHiddenInEditor: Bool;
  native let isLocked: Bool;
  native let boundLibraryItemName: CName;
}
