
public native class inkSystem extends IGameSystem {
    private let m_clipboard: String;

    public native func GetLayers() -> array<ref<inkLayerWrapper>>
    public native func GetLayer(layer: CName) -> ref<inkLayerWrapper>

    public func GetClipboard() -> String {
        return this.m_clipboard;
    }

    public func SetClipboard(data: String) {
        this.m_clipboard = data;
    }
}

@addMethod(GameInstance)
public static native func GetInkSystem() -> ref<inkSystem>
