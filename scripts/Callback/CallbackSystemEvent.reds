// Game 2.5 declares `native class CallbackSystemEvent extends IScriptable { native let eventName: CName; }`.
@addMethod(CallbackSystemEvent)
public native func GetEventName() -> CName
