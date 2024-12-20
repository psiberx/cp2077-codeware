@addMethod(worlduiIGameController)
public func GetWorldWidgetComponent() -> ref<IComponent> {
    let widget = this.GetRootWidget();
    while IsDefined(widget) {
        let userData = widget.GetUserData(n"inkWorldWidgetInfos") as inkWorldWidgetInfos;
        if IsDefined(userData) {
            return userData.GetComponent();
        }
        widget = widget.parentWidget;
    }

    return null;
}
