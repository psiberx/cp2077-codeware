public native class CodewareCallbackSystemHandler {
    public native func AddTarget(target: ref<CodewareCallbackSystemTarget>) -> ref<CodewareCallbackSystemHandler>
    public native func RemoveTarget(target: ref<CodewareCallbackSystemTarget>) -> ref<CodewareCallbackSystemHandler>

    public native func SetRunMode(runMode: CallbackRunMode) -> ref<CodewareCallbackSystemHandler>
    public native func SetLifetime(lifetime: CallbackLifetime) -> ref<CodewareCallbackSystemHandler>

    public native func IsRegistered() -> Bool
    public native func Unregister()
}
