// -----------------------------------------------------------------------------
// Codeware.UI.InGamePopupFooter
// -----------------------------------------------------------------------------

module Codeware.UI

public class InGamePopupFooter extends inkCustomController {
    protected let m_fluffIcon: wref<inkImage>;

    protected let m_fluffText: wref<inkText>;

    protected let m_inputHolder: wref<inkCompoundWidget>;

    protected let m_buttonHints: wref<ButtonHintsEx>;

    protected cb func OnCreate() {
        let footer: ref<inkCanvas> = new inkCanvas();
        footer.SetName(n"footer");
        footer.SetAnchor(inkEAnchor.BottomFillHorizontaly);

        let line: ref<inkRectangle> = new inkRectangle();
        line.SetName(n"line");
        line.SetMargin(inkMargin(76.0, 0.0, 76.0, 90.0));
        line.SetAnchor(inkEAnchor.BottomFillHorizontaly);
        line.SetAnchorPoint(Vector2(0.5, 0.5));
        line.SetOpacity(0.133);
        line.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        line.BindProperty(n"tintColor", n"MainColors.Red");
        line.SetSize(Vector2(1170.0, 2.0));
        line.SetRenderTransformPivot(Vector2(0.0, 0.5));
        line.Reparent(footer);

        let fluffIcon: ref<inkImage> = new inkImage();
        fluffIcon.SetName(n"fluffIcon");
        fluffIcon.SetVisible(false);
        fluffIcon.SetAtlasResource(r"base\\gameplay\\gui\\widgets\\scanning\\scanner_tooltip\\atlas_scanner.inkatlas");
        fluffIcon.SetFitToContent(true);
        fluffIcon.SetMargin(inkMargin(76.0, 0.0, 0.0, 10.0));
        fluffIcon.SetHAlign(inkEHorizontalAlign.Center);
        fluffIcon.SetVAlign(inkEVerticalAlign.Center);
        fluffIcon.SetAnchor(inkEAnchor.BottomLeft);
        fluffIcon.SetAnchorPoint(Vector2(0.0, 1.0));
        fluffIcon.SetOpacity(0.217);
        fluffIcon.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        fluffIcon.BindProperty(n"tintColor", n"MainColors.Red");
        fluffIcon.SetSize(Vector2(32.0, 32.0));
        fluffIcon.Reparent(footer);

        let fluffText: ref<inkText> = new inkText();
        fluffText.SetName(n"fluffText");
        fluffText.SetVisible(false);
        fluffText.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
        fluffText.SetFontStyle(n"Regular");
        fluffText.SetFontSize(20);
        fluffText.SetFitToContent(true);
        fluffText.SetMargin(inkMargin(135.0, 0.0, 0.0, 75.0));
        fluffText.SetAnchor(inkEAnchor.BottomLeft);
        fluffText.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        fluffText.BindProperty(n"tintColor", n"MainColors.Red");
        fluffText.SetSize(Vector2(100.0, 32.0));
        fluffText.Reparent(footer);

        let inputHolder: ref<inkCanvas> = new inkCanvas();
        inputHolder.SetName(n"inputHolder");
        inputHolder.SetFitToContent(true);
        inputHolder.SetHAlign(inkEHorizontalAlign.Right);
        inputHolder.SetAnchor(inkEAnchor.BottomRight);
        inputHolder.SetAnchorPoint(Vector2(1.0, 1.0));
        inputHolder.SetRenderTransformPivot(Vector2(1.0, 1.0));
        inputHolder.SetMargin(inkMargin(0.0, 0.0, 32.0, 0.0));
        inputHolder.Reparent(footer);

        this.m_fluffIcon = fluffIcon;
        this.m_fluffText = fluffText;
        this.m_inputHolder = inputHolder;

        this.SetRootWidget(footer);
    }

    protected cb func OnInitialize() {
        this.m_buttonHints = ButtonHintsManager.GetInstance().SpawnButtonHints(this.m_inputHolder);
        this.m_buttonHints.SetStyle(n"popup");
        this.m_buttonHints.AddButtonHint(n"cancel", "UI-UserActions-Close");
    }

    public func GetHints() -> wref<ButtonHintsEx> {
        return this.m_buttonHints;
    }

    public func SetFluffIcon(icon: CName) {
        this.m_fluffIcon.SetTexturePart(icon);
        this.m_fluffIcon.SetVisible(true);
    }

    public func SetFluffIcon(icon: CName, atlas: ResRef) {
        this.m_fluffIcon.SetAtlasResource(atlas);
        this.m_fluffIcon.SetTexturePart(icon);
        this.m_fluffIcon.SetVisible(true);
    }

    public func SetFluffText(text: String) {
        this.m_fluffText.SetText(text);
        this.m_fluffText.SetVisible(true);
    }

    public static func Create() -> ref<InGamePopupFooter> {
        let self: ref<InGamePopupFooter> = new InGamePopupFooter();
        self.CreateInstance();

        return self;
    }
}
