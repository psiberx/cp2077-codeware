public native class inkKeyInputEvent extends inkInputEvent {
    public native func GetKey() -> EInputKey
    public native func GetAction() -> EInputAction
    public native func GetCharacter() -> String
    public native func IsCharacter() -> Bool
}
