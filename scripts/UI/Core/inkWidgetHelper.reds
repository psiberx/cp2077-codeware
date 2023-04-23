// -----------------------------------------------------------------------------
// Codeware.UI.inkWidgetHelper
// -----------------------------------------------------------------------------
//
// public abstract class inkWidgetHelper {
//   public static func InWindowTree(widget: ref<inkWidget>) -> Bool
// }
//

module Codeware.UI

public abstract class inkWidgetHelper {
    public static func InWindowTree(widget: ref<inkWidget>) -> Bool {
        while (IsDefined(widget)) {
            if widget.IsA(n"inkVirtualWindow") {
                return true;
            }

            widget = widget.GetParentWidget();
        }

        return false;
    }

    public static func GetControllersByType(widget: ref<inkWidget>, controllerType: CName, out controllers: array<ref<inkLogicController>>) {
        let controller = widget.GetControllerByType(controllerType);
        if IsDefined(controller) {
            ArrayPush(controllers, controller);
        } else {
            let container = widget as inkCompoundWidget;
            if IsDefined(container) {
                let i = 0;
                let n = container.GetNumChildren();
                while i < n {
                    inkWidgetHelper.GetControllersByType(container.GetWidget(i), controllerType, controllers);
                    i += 1;
                }
            }
        }
    }
}
