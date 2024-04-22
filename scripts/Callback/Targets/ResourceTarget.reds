public native class ResourceTarget extends CallbackSystemTarget {
    public static native func Path(resourcePath: ResRef) -> ref<ResourceTarget>
    public static native func Type(resourceType: CName) -> ref<ResourceTarget>
}
