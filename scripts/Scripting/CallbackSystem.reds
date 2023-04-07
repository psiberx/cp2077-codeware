
public native class CallbackSystem extends IGameSystem {
    public native func RegisterCallback(event: CName, target: ref<IScriptable>, function: CName, opt global: Bool)
    public native func UnregisterCallback(event: CName, target: ref<IScriptable>, function: CName)
    public native func RegisterStaticCallback(event: CName, target: CName, function: CName, opt global: Bool)
    public native func UnregisterStaticCallback(event: CName, target: CName, function: CName)
}

@addMethod(GameInstance)
public static native func GetCallbackSystem() -> ref<CallbackSystem>
