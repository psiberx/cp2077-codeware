public native class CallbackSystem extends IGameSystem {
    public native func RegisterCallback(event: CName, target: ref<IScriptable>, function: CName, opt sticky: Bool) -> ref<CallbackSystemHandler>
    public native func RegisterStaticCallback(event: CName, target: CName, function: CName, opt sticky: Bool) -> ref<CallbackSystemHandler>

    public native func UnregisterCallback(event: CName, target: ref<IScriptable>, opt function: CName)
    public native func UnregisterStaticCallback(event: CName, target: CName, opt function: CName)

    public native func FireCallbacks(event: ref<CallbackSystemEvent>)
}

@addMethod(GameInstance)
public static native func GetCallbackSystem() -> ref<CallbackSystem>
