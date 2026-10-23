public native class CodewareResourceEvent extends CodewareCallbackSystemEvent {
    public native func GetResource() -> ref<CResource>
    public native func GetPath() -> ResRef
    public native func GetJobGroup() -> JobGroup
}
