public native class inkWidgetSpawnEvent extends CallbackSystemEvent {
    public native func GetLibraryPath() -> ResRef
    public native func GetItemName() -> CName
    public native func GetItemInstance() -> ref<inkWidgetLibraryItemInstance>
}
