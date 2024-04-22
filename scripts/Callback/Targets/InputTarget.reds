public native class InputTarget extends CallbackSystemTarget {
    public static native func Key(key: EInputKey, opt action: EInputAction) -> ref<InputTarget>
    public static native func Axis(axis: EInputKey, opt threshold: Float) -> ref<InputTarget>
}
