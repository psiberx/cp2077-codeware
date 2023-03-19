// -----------------------------------------------------------------------------
// inkWidget
// -----------------------------------------------------------------------------
//
// - Parent widget
// - Primary logic controller
// - Secondary logic controllers
// - Custom user data
//
// -----------------------------------------------------------------------------
//
// class inkWidget {
//   public func GetParentWidget() -> wref<inkWidget>
//   public func AttachController(controller: ref<inkLogicController>, opt secondary: Bool)
//   public func SetUserData(userData: ref<inkUserData>)
// }
//

@addField(inkWidget)
native let parentWidget: wref<inkWidget>;

@addField(inkWidget)
native let logicController: ref<inkLogicController>;

@addField(inkWidget)
native let secondaryControllers: array<ref<inkLogicController>>;

@addField(inkWidget)
native let userData: array<ref<inkUserData>>;

@addField(inkWidget)
native let canSupportFocus: Bool;

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
public native func AttachController(controller: ref<inkLogicController>, opt secondary: Bool);
