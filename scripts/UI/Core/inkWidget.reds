@addMethod(inkWidget)
public func GetParentWidget() -> wref<inkWidget> {
    return this.parentWidget;
}

@addMethod(inkWidget)
public func SetUserData(userData: ref<inkUserData>) {
    ArrayPush(this.userData, userData);
}

@addMethod(inkWidget)
public func CanSupportFocus() -> Bool {
    return this.canSupportFocus;
}

@addMethod(inkWidget)
public func SetSupportFocus(enabled: Bool) {
    this.canSupportFocus = enabled;
}

@addMethod(inkWidget)
public func AddEffect(effect: ref<inkIEffect>) {
    ArrayPush(this.effects, effect);
}

@addMethod(inkWidget)
public native func AttachController(controller: ref<inkLogicController>, opt secondary: Bool);
