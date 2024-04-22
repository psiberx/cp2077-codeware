public native class CallbackSystemHandler {
    public native func AddTarget(target: ref<CallbackSystemTarget>) -> ref<CallbackSystemHandler>
    public native func RemoveTarget(target: ref<CallbackSystemTarget>) -> ref<CallbackSystemHandler>

    public native func SetRunMode(runMode: CallbackRunMode) -> ref<CallbackSystemHandler>
    public native func SetLifetime(lifetime: CallbackLifetime) -> ref<CallbackSystemHandler>

    public native func IsRegistered() -> Bool
    public native func Unregister()
}
