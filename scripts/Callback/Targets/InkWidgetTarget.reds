public native class inkWidgetTarget extends CodewareCallbackSystemTarget {
    public static native func Library(library: ResRef, opt item: CName) -> ref<inkWidgetTarget>
    public static native func Controller(type: CName) -> ref<inkWidgetTarget>
}
