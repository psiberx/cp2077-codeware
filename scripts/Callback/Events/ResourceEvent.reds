public native class ResourceEvent extends CallbackSystemEvent {
    public native func GetResource() -> ref<CResource>
    public native func GetPath() -> ResRef
    public native func GetJobGroup() -> JobGroup
}
