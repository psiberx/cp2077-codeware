public native class ResourceDepot {
    public native func ArchiveExists(name: String) -> Bool
    public native func ResourceExists(path: ResRef) -> Bool
    public native func LoadResource(path: ResRef) -> ref<ResourceToken>
    public native func RemoveResourceFromCache(path: ResRef)
}

@addMethod(GameInstance)
public static native func GetResourceDepot() -> ref<ResourceDepot>
