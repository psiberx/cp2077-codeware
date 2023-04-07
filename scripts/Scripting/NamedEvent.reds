
public abstract native class NamedEvent {
    protected native func InitEvent(name: CName)
    public native func GetEventName() -> CName
}
