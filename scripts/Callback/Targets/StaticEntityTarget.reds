public native class StaticEntityTarget extends CodewareCallbackSystemTarget {
    public static native func Tag(tag: CName) -> ref<StaticEntityTarget>
    public static native func Tags(tags: array<CName>) -> ref<StaticEntityTarget>
}
