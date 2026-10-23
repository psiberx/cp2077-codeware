// Game 2.5 declares `native class inkKeyInputEvent extends inkInputEvent` with the fields key, action,
// character and IsCharacter().
@addMethod(inkKeyInputEvent)
public native func GetKey() -> EInputKey

@addMethod(inkKeyInputEvent)
public native func GetAction() -> EInputAction

@addMethod(inkKeyInputEvent)
public native func GetCharacter() -> String
