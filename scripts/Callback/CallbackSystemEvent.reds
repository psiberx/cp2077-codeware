public abstract native class CallbackSystemEvent {
    protected native func InitEvent(name: CName)
    public native func GetEventName() -> CName
}
