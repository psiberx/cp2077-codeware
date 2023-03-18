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
//   public func SetController(controller: ref<inkLogicController>)
//   public func AddSecondaryController(controller: ref<inkLogicController>)
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
public native func SetController(controller: ref<inkLogicController>);

@addMethod(inkWidget)
public native func AddSecondaryController(controller: ref<inkLogicController>);

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
