// -----------------------------------------------------------------------------
// Codeware.UI.InMenuPopupFooter
// -----------------------------------------------------------------------------

module Codeware.UI

public class InMenuPopupFooter extends inkCustomController {
    protected cb func OnCreate() {
        let buttons: ref<inkHorizontalPanel> = new inkHorizontalPanel();
        buttons.SetName(n"Buttons");
        buttons.SetFitToContent(true);
        buttons.SetMargin(inkMargin(-40.0, 0.0, -100.0, 0.0));
        buttons.SetHAlign(inkEHorizontalAlign.Right);
        buttons.SetChildMargin(inkMargin(10.0, 0.0, 0.0, 0.0));

        this.SetRootWidget(buttons);
    }

    public static func Create() -> ref<InMenuPopupFooter> {
        let self = new InMenuPopupFooter();
        self.CreateInstance();

        return self;
    }
}
