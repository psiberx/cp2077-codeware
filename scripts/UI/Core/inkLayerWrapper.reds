public native class inkLayerWrapper {
    public native func GetLayerName() -> CName
    public native func GetVirtualWindow() -> wref<inkVirtualWindow>
    public native func GetGameController() -> wref<inkIGameController>
    public native func GetGameControllers() -> array<wref<inkIGameController>>
}
