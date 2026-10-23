public native class CodewareCallbackSystem extends IGameSystem {
    public native func RegisterCallback(eventName: CName, target: ref<IScriptable>, function: CName, opt sticky: Bool) -> ref<CodewareCallbackSystemHandler>
    public native func RegisterStaticCallback(eventName: CName, target: CName, function: CName, opt sticky: Bool) -> ref<CodewareCallbackSystemHandler>

    public native func UnregisterCallback(eventName: CName, target: ref<IScriptable>, opt function: CName)
    public native func UnregisterStaticCallback(eventName: CName, target: CName, opt function: CName)

    public native func RegisterEvent(eventName: CName, opt eventType: CName) -> Bool

    public native func DispatchEvent(eventObject: ref<CodewareCallbackSystemEvent>)
    public native func DispatchEventAs(eventName: CName, eventObject: ref<CodewareCallbackSystemEvent>)
}

@addMethod(GameInstance)
public static native func GetCodewareCallbackSystem() -> ref<CodewareCallbackSystem>
