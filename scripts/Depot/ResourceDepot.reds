public native class ResourceDepot {
    public native func IsArchiveExists(name: String) -> Bool
    public native func IsResourceExists(path: ResRef) -> Bool
}

@addMethod(GameInstance)
public static native func GetResourceDepot() -> ref<ResourceDepot>
