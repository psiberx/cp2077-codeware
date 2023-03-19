
public native class inkWindow extends inkCanvas {}

public native class inkVirtualWindow extends inkWindow {
    public native func GetLayerName() -> CName
    public native func GetGameController() -> wref<inkIGameController>
    public native func GetGameControllers() -> array<wref<inkIGameController>>
}
