
public native class inkSystem {
    public native func GetLayers() -> array<ref<inkLayerWrapper>>
    public native func GetLayer(layer: CName) -> ref<inkLayerWrapper>
}

@addMethod(GameInstance)
public static native func GetInkSystem() -> ref<inkSystem>
