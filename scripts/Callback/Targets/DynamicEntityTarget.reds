public native class DynamicEntityTarget extends CodewareCallbackSystemTarget {
    public static native func Tag(tag: CName) -> ref<DynamicEntityTarget>
    public static native func Tags(tags: array<CName>) -> ref<DynamicEntityTarget>
}
