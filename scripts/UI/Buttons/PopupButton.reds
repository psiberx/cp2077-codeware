// -----------------------------------------------------------------------------
// Codeware.UI.PopupButton
// -----------------------------------------------------------------------------

module Codeware.UI

public class PopupButton extends CustomButton {
    protected let m_isFlipped: Bool;

    protected let m_bg: wref<inkImage>;
    protected let m_frame: wref<inkImage>;
    protected let m_input: wref<inkInputDisplayController>;

    protected func CreateWidgets() {
        let root = new inkFlex();
        root.SetName(n"button");
        root.SetInteractive(true);
        root.SetMargin(inkMargin(0.0, 20.0, 0.0, 0.0));
        root.SetHAlign(inkEHorizontalAlign.Right);
        root.SetVAlign(inkEVerticalAlign.Top);
        root.SetSize(Vector2(100.0, 100.0));
        //root.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");

        let minSize = new inkRectangle();
        minSize.SetName(n"minSize");
        minSize.SetVisible(false);
        minSize.SetAffectsLayoutWhenHidden(true);
        minSize.SetHAlign(inkEHorizontalAlign.Left);
        minSize.SetVAlign(inkEVerticalAlign.Top);
        minSize.SetSize(Vector2(326.0, 80.0));
        minSize.Reparent(root);

        let background = new inkImage();
        background.SetName(n"background");
        background.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        background.SetTexturePart(n"cell_bg");
        background.SetNineSliceScale(true);
        background.SetAnchorPoint(Vector2(0.5, 0.5));
        background.SetSize(Vector2(326.0, 80.0));
        background.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");
        background.BindProperty(n"tintColor", n"PopupButton.bgColor");
        background.BindProperty(n"opacity", n"PopupButton.bgOpacity");
        background.Reparent(root);

        let frame = new inkImage();
        frame.SetName(n"frame");
        frame.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        frame.SetTexturePart(n"cell_fg");
        frame.SetNineSliceScale(true);
        frame.SetVAlign(inkEVerticalAlign.Top);
        frame.SetAnchorPoint(Vector2(0.5, 0.5));
        frame.SetSize(Vector2(326.0, 80.0));
        frame.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");
        frame.BindProperty(n"tintColor", n"PopupButton.frameColor");
        frame.BindProperty(n"opacity", n"PopupButton.frameOpacity");
        frame.Reparent(root);

        let content = new inkHorizontalPanel();
        content.SetName(n"content");
        content.SetFitToContent(true);
        content.SetMargin(inkMargin(15.0, 0.0, 0.0, 0.0));
        content.SetHAlign(inkEHorizontalAlign.Left);
        content.Reparent(root);
        
        let inputDisplay = new inkHorizontalPanel();
        inputDisplay.SetName(n"inputDisplay");
        inputDisplay.SetFitToContent(true);
        inputDisplay.SetMargin(inkMargin(0.0, 0.0, 12.0, 0.0));
        inputDisplay.SetHAlign(inkEHorizontalAlign.Left);
        inputDisplay.SetVAlign(inkEVerticalAlign.Center);
        inputDisplay.SetSize(Vector2(40.0, 32.0));
        inputDisplay.Reparent(content);

        let inputRoot = new inkCanvas();
        inputRoot.SetName(n"inputRoot");
        inputRoot.SetHAlign(inkEHorizontalAlign.Left);
        inputRoot.SetVAlign(inkEVerticalAlign.Top);
        inputRoot.SetSize(Vector2(64.0, 64.0));
        inputRoot.Reparent(inputDisplay);

        let inputIcon = new inkImage();
        inputIcon.SetName(n"inputIcon");
        inputIcon.SetAtlasResource(r"base\\gameplay\\gui\\common\\input\\icons_keyboard.inkatlas");
        inputIcon.SetTexturePart(n"kb_enter");
        inputIcon.SetAffectsLayoutWhenHidden(true);
        inputIcon.SetHAlign(inkEHorizontalAlign.Center);
        inputIcon.SetVAlign(inkEVerticalAlign.Center);
        inputIcon.SetAnchor(inkEAnchor.Centered);
        inputIcon.SetAnchorPoint(Vector2(0.5, 0.5));
        inputIcon.SetSize(Vector2(64.0, 64.0));
        inputIcon.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");
        inputIcon.BindProperty(n"tintColor", n"PopupButton.iconColor");
        inputIcon.BindProperty(n"opacity", n"PopupButton.iconOpacity");
        inputIcon.Reparent(inputRoot);

        let inputText = new inkText();
        inputText.SetName(n"inputText");
        inputText.SetVisible(false);
        inputText.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
        inputText.SetFontStyle(n"Regular");
        inputText.SetFontSize(45);
        inputText.SetFitToContent(true);
        inputText.SetAnchor(inkEAnchor.Centered);
        inputText.SetAnchorPoint(Vector2(0.5, 0.5));
        inputText.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");
        inputText.BindProperty(n"tintColor", n"PopupButton.iconColor");
        inputText.BindProperty(n"opacity", n"PopupButton.iconOpacity");
        inputText.Reparent(inputRoot);

        let inputController = new inkInputDisplayController();
        inputController.fixedIconHeight = 64;
        inputController.iconRef = inkWidgetRef.Create(inputIcon);
        inputController.nameRef = inkWidgetRef.Create(inputText);
        inputController.canvasRef = inkWidgetRef.Create(inputRoot);
        inputDisplay.AttachController(inputController);

        let label = new inkText();
        label.SetName(n"label");
        label.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
        label.SetLetterCase(textLetterCase.UpperCase);
        label.SetLineHeight(0.9);
        label.SetHorizontalAlignment(textHorizontalAlignment.Center);
        label.SetVerticalAlignment(textVerticalAlignment.Center);
        label.SetContentHAlign(inkEHorizontalAlign.Center);
        label.SetContentVAlign(inkEVerticalAlign.Center);
        label.SetOverflowPolicy(textOverflowPolicy.AdjustToSize);
        label.SetFitToContent(true);
        label.SetVAlign(inkEVerticalAlign.Center);
        label.SetSize(Vector2(100.0, 32.0));
        label.SetStyle(r"base\\gameplay\\gui\\common\\dialogs_popups.inkstyle");
        label.BindProperty(n"fontStyle", n"MainColors.BodyFontWeight");
        label.BindProperty(n"fontSize", n"MainColors.ReadableMedium");
        label.BindProperty(n"tintColor", n"PopupButton.textColor");
        label.BindProperty(n"opacity", n"PopupButton.textOpacity");
        label.Reparent(content);

        this.m_root = root;
        this.m_label = label;
        this.m_bg = background;
        this.m_frame = frame;
        this.m_input = inputController;

        this.SetRootWidget(root);
        this.ApplyFlippedState();
        this.ApplyInputState();
    }

    protected func ApplyFlippedState() {
        this.m_bg.SetTexturePart(this.m_isFlipped ? n"cell_flip_bg" : n"cell_bg");
        this.m_frame.SetTexturePart(this.m_isFlipped ? n"cell_flip_fg" : n"cell_fg");
    }

    protected func ApplyInputState() {
        if NotEquals(this.m_input.GetInputAction(), n"") {
            this.m_input.SetVisible(true);
            this.m_label.SetMargin(inkMargin(0.0, 0.0, 20.0, 0.0));
        } else {
            this.m_input.SetVisible(false);
            this.m_label.SetMargin(inkMargin(10.0, 0.0, 20.0, 0.0));
        }
    }

    protected func ApplyHoveredState() {
        this.m_root.SetState(this.m_isHovered ? n"Hover" : n"Default");
    }

    public func SetFlipped(isFlipped: Bool) {
        this.m_isFlipped = isFlipped;

        this.ApplyFlippedState();
    }

    public func GetInputAction() -> CName {
        return this.m_input.GetInputAction();
    }

    public func SetInputAction(action: CName) {
        this.m_input.SetInputAction(action);

        this.ApplyInputState();
    }

    public func SetInputKey(input: inkInputKeyData) {
        this.m_input.SetInputKey(input);

        this.ApplyInputState();
    }

    public static func Create() -> ref<PopupButton> {
        let self = new PopupButton();
        self.CreateInstance();

        return self;
    }
}
