public native class KeyInputEvent extends CallbackSystemEvent {
    public native func GetAction() -> EInputAction
    public native func GetKey() -> EInputKey
    public native func IsShiftDown() -> Bool
    public native func IsControlDown() -> Bool
    public native func IsAltDown() -> Bool
}
