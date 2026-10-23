public native class CodewareInputTarget extends CodewareCallbackSystemTarget {
    public static native func Key(key: EInputKey, opt action: EInputAction) -> ref<CodewareInputTarget>
    public static native func Axis(axis: EInputKey, opt threshold: Float) -> ref<CodewareInputTarget>
}
