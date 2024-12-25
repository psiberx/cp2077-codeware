public native class inkSystem extends IGameSystem {
    private let m_clipboard: String;

    public native func GetLayers() -> array<ref<inkLayerWrapper>>
    public native func GetLayer(layer: CName) -> ref<inkLayerWrapper>
    public native func GetWorldWidgets() -> array<wref<inkIGameController>>

    public native func GetClipboardText() -> String
    public native func SetClipboardText(data: String)

    public func SetFocus(widget: ref<inkWidget>) {
        GameInstance.GetInkSystem().GetLayer(n"inkGameNotificationsLayer").GetGameController().RequestSetFocus(widget);
    }

    public func ResetFocus() {
        this.SetFocus(null);
    }
}

@addMethod(GameInstance)
public static native func GetInkSystem() -> ref<inkSystem>
