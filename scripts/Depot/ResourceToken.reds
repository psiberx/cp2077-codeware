public native class ResourceToken {
    public native func GetResource() -> ref<CResource>
    public native func GetPath() -> ResRef
    public native func GetHash() -> Uint64
    public native func IsFinished() -> Bool
    public native func IsLoaded() -> Bool
    public native func IsFailed() -> Bool
    public native func RegisterCallback(target: ref<IScriptable>, function: CName)
}
