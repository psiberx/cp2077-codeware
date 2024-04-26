public native class StaticEntityTarget extends CallbackSystemTarget {
    public static native func Tag(tag: CName) -> ref<StaticEntityTarget>
    public static native func Tags(tags: array<CName>) -> ref<StaticEntityTarget>
}
