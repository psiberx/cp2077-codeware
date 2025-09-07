// -----------------------------------------------------------------------------
// Codeware.UI.InMenuPopupContent
// -----------------------------------------------------------------------------

module Codeware.UI

public class InMenuPopupContent extends inkCustomController {
    protected let m_content: wref<inkFlex>;
    protected let m_title: wref<inkText>;

    protected cb func OnCreate() {
        let main: ref<inkFlex> = new inkFlex();
        main.SetName(n"main");
        main.SetAffectsLayoutWhenHidden(true);
        main.SetSize(Vector2(100.0, 100.0));

        let minSize: ref<inkCanvas> = new inkCanvas();
        minSize.SetName(n"minSize");
        minSize.SetVisible(false);
        minSize.SetAffectsLayoutWhenHidden(true);
        minSize.SetVAlign(inkEVerticalAlign.Top);
        minSize.SetSize(Vector2(1380.0, 240.0));
        minSize.Reparent(main);

        let wrapper: ref<inkHorizontalPanel> = new inkHorizontalPanel();
        wrapper.SetName(n"wrapper");
        wrapper.SetFitToContent(true);
        wrapper.SetSize(Vector2(100.0, 100.0));
        wrapper.Reparent(main);

        let left: ref<inkFlex> = new inkFlex();
        left.SetName(n"left");
        left.SetInteractive(true);
        left.SetMargin(inkMargin(-1.0, 0.0, 0.0, 0.0));
        left.SetHAlign(inkEHorizontalAlign.Left);
        left.SetAnchor(inkEAnchor.LeftFillVerticaly);
        left.SetAnchorPoint(Vector2(1.0, 0.0));
        left.SetSize(Vector2(40.0, 400.0));
        left.Reparent(wrapper);

        let sidePartFg: ref<inkImage> = new inkImage();
        sidePartFg.SetName(n"sidePart_fg");
        sidePartFg.SetState(n"Common");
        sidePartFg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        sidePartFg.SetTexturePart(n"notification_bracket_simple_fg");
        sidePartFg.SetNineSliceScale(true);
        sidePartFg.SetMargin(inkMargin(-2.0, 0.0, 0.0, 0.0));
        sidePartFg.SetHAlign(inkEHorizontalAlign.Left);
        sidePartFg.SetAnchor(inkEAnchor.Fill);
        sidePartFg.SetAnchorPoint(Vector2(1.0, 0.5));
        sidePartFg.SetOpacity(0.5);
        sidePartFg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        sidePartFg.BindProperty(n"tintColor", n"MainColors.Red");
        sidePartFg.SetSize(Vector2(40.0, 32.0));
        sidePartFg.Reparent(left);

        let sidePartBg: ref<inkImage> = new inkImage();
        sidePartBg.SetName(n"sidePart_bg");
        sidePartBg.SetState(n"Common");
        sidePartBg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        sidePartBg.SetTexturePart(n"notification_bracket_simple_bg");
        sidePartBg.SetNineSliceScale(true);
        sidePartBg.SetMargin(inkMargin(-2.0, 0.0, 0.0, 0.0));
        sidePartBg.SetHAlign(inkEHorizontalAlign.Left);
        sidePartBg.SetAnchor(inkEAnchor.Fill);
        sidePartBg.SetAnchorPoint(Vector2(1.0, 0.5));
        sidePartBg.SetOpacity(0.5);
        sidePartBg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        sidePartBg.BindProperty(n"tintColor", n"MainColors.MildRed");
        sidePartBg.SetSize(Vector2(40.0, 30.0));
        sidePartBg.Reparent(left);

        let sidePartAccent: ref<inkImage> = new inkImage();
        sidePartAccent.SetName(n"sidePart_accent");
        sidePartAccent.SetState(n"Common");
        sidePartAccent.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        sidePartAccent.SetTexturePart(n"perk_cell_side_accent");
        sidePartAccent.SetHAlign(inkEHorizontalAlign.Left);
        sidePartAccent.SetVAlign(inkEVerticalAlign.Center);
        sidePartAccent.SetAnchor(inkEAnchor.CenterLeft);
        sidePartAccent.SetAnchorPoint(Vector2(0.0, 0.5));
        sidePartAccent.SetOpacity(0.2);
        sidePartAccent.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        sidePartAccent.BindProperty(n"tintColor", n"MainColors.Red");
        sidePartAccent.SetSize(Vector2(28.0, 8.0));
        sidePartAccent.SetRotation(180.0);
        sidePartAccent.Reparent(left);

        let right: ref<inkFlex> = new inkFlex();
        right.SetName(n"right");
        right.SetAffectsLayoutWhenHidden(true);
        right.SetSizeRule(inkESizeRule.Stretch);
        right.SetSize(Vector2(1128.0, 400.0));
        right.Reparent(wrapper);

        let accentBg: ref<inkImage> = new inkImage();
        accentBg.SetName(n"accent_bg");
        accentBg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        accentBg.SetTexturePart(n"tooltip_b_bracket_light_bg");
        accentBg.SetNineSliceScale(true);
        accentBg.SetMargin(inkMargin(0.0, 0.0, -8.0, 0.0));
        accentBg.SetHAlign(inkEHorizontalAlign.Right);
        accentBg.SetVAlign(inkEVerticalAlign.Center);
        accentBg.SetAnchorPoint(Vector2(0.5, 0.5));
        accentBg.SetOpacity(0.05);
        accentBg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        accentBg.BindProperty(n"tintColor", n"MainColors.MildRed");
        accentBg.SetSize(Vector2(10.0, 160.0));
        accentBg.SetRenderTransformPivot(Vector2(0.0, 0.0));
        accentBg.Reparent(right);

        let accentFg: ref<inkImage> = new inkImage();
        accentFg.SetName(n"accent_fg");
        accentFg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        accentFg.SetTexturePart(n"tooltip_b_bracket_light_fg");
        accentFg.SetNineSliceScale(true);
        accentFg.SetMargin(inkMargin(0.0, 0.0, -8.0, 0.0));
        accentFg.SetHAlign(inkEHorizontalAlign.Right);
        accentFg.SetVAlign(inkEVerticalAlign.Center);
        accentFg.SetAnchorPoint(Vector2(0.5, 0.5));
        accentFg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        accentFg.BindProperty(n"tintColor", n"MainColors.Red");
        accentFg.SetSize(Vector2(10.0, 160.0));
        accentFg.SetRenderTransformPivot(Vector2(0.0, 0.0));
        accentFg.Reparent(right);

        let protocol: ref<inkImage> = new inkImage();
        protocol.SetName(n"protocol");
        protocol.SetAtlasResource(r"base\\gameplay\\gui\\common\\icons\\atlas_common.inkatlas");
        protocol.SetTexturePart(n"fluff_protocol1");
        protocol.SetContentHAlign(inkEHorizontalAlign.Left);
        protocol.SetContentVAlign(inkEVerticalAlign.Top);
        protocol.SetFitToContent(true);
        protocol.SetMargin(inkMargin(0.0, -54.0, 0.0, 0.0));
        protocol.SetHAlign(inkEHorizontalAlign.Left);
        protocol.SetVAlign(inkEVerticalAlign.Top);
        protocol.SetAnchorPoint(Vector2(0.5, 0.5));
        protocol.SetOpacity(0.3);
        protocol.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        protocol.BindProperty(n"tintColor", n"MainColors.MildRed");
        protocol.SetSize(Vector2(32.0, 32.0));
        protocol.SetRenderTransformPivot(Vector2(0.0, 0.5));
        protocol.SetScale(Vector2(0.3, 0.3));
        protocol.Reparent(right);

        let bg: ref<inkImage> = new inkImage();
        bg.SetName(n"bg");
        bg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        bg.SetTexturePart(n"cell_bg");
        bg.SetNineSliceScale(true);
        bg.SetAffectsLayoutWhenHidden(true);
        bg.SetFitToContent(true);
        bg.SetAnchor(inkEAnchor.Fill);
        bg.SetAnchorPoint(Vector2(0.5, 0.5));
        bg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        bg.BindProperty(n"tintColor", n"MainColors.Fullscreen_PrimaryBackgroundDarkest");
        bg.SetSize(Vector2(32.0, 32.0));
        bg.SetRenderTransformPivot(Vector2(0.0, 0.5));
        bg.Reparent(right);

        let fg: ref<inkImage> = new inkImage();
        fg.SetName(n"fg");
        fg.SetAtlasResource(r"base\\gameplay\\gui\\common\\shapes\\atlas_shapes_sync.inkatlas");
        fg.SetTexturePart(n"cell_fg");
        fg.SetNineSliceScale(true);
        fg.SetAffectsLayoutWhenHidden(true);
        fg.SetFitToContent(true);
        fg.SetMargin(inkMargin(-1.000002, 0.967965, 1.000002, -0.967965));
        fg.SetAnchor(inkEAnchor.Fill);
        fg.SetAnchorPoint(Vector2(0.5, 0.5));
        fg.SetOpacity(0.1);
        fg.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        fg.BindProperty(n"tintColor", n"MainColors.Red");
        fg.SetSize(Vector2(32.0, 32.0));
        fg.SetRenderTransformPivot(Vector2(0.0, 0.5));
        fg.Reparent(right);

        let fluffText1: ref<inkImage> = new inkImage();
        fluffText1.SetName(n"fluffText1");
        fluffText1.SetAtlasResource(r"base\\gameplay\\gui\\fullscreen\\inventory\\atlas_inventory.inkatlas");
        fluffText1.SetTexturePart(n"fluffcc35_3");
        fluffText1.SetFitToContent(true);
        fluffText1.SetMargin(inkMargin(10.0, 0.0, 0.0, 10.0));
        fluffText1.SetHAlign(inkEHorizontalAlign.Left);
        fluffText1.SetVAlign(inkEVerticalAlign.Bottom);
        fluffText1.SetAnchor(inkEAnchor.BottomLeft);
        fluffText1.SetAnchorPoint(Vector2(0.5, 0.5));
        fluffText1.SetOpacity(0.3);
        fluffText1.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        fluffText1.BindProperty(n"tintColor", n"MainColors.MildRed");
        fluffText1.SetSize(Vector2(30.0, 30.0));
        fluffText1.Reparent(right);

        let warningIcon: ref<inkCanvas> = new inkCanvas();
        warningIcon.SetName(n"warning_icon");
        warningIcon.SetState(n"error_no");
        warningIcon.SetVisible(false);
        warningIcon.SetInteractive(true);
        warningIcon.SetMargin(inkMargin(70.0, 24.0, 0.0, 0.0));
        warningIcon.SetHAlign(inkEHorizontalAlign.Left);
        warningIcon.SetVAlign(inkEVerticalAlign.Top);
        warningIcon.SetSize(Vector2(100.0, 100.0));
        warningIcon.Reparent(main);

        let icon: ref<inkImage> = new inkImage();
        icon.SetName(n"icon");
        icon.SetAtlasResource(r"base\\gameplay\\gui\\fullscreen\\common\\fullscreen_elements.inkatlas");
        icon.SetTexturePart(n"fluff_attention_fill");
        icon.SetFitToContent(true);
        icon.SetMargin(inkMargin(0.0, 10.0, 0.0, 0.0));
        icon.SetHAlign(inkEHorizontalAlign.Center);
        icon.SetVAlign(inkEVerticalAlign.Center);
        icon.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        icon.BindProperty(n"tintColor", n"MainColors.Red");
        icon.SetSize(Vector2(74.0, 64.0));
        icon.SetRenderTransformPivot(Vector2(0.0, 0.0));
        icon.SetScale(Vector2(0.5, 0.5));
        icon.Reparent(warningIcon);

        let inkVerticalPanelWidget18: ref<inkVerticalPanel> = new inkVerticalPanel();
        inkVerticalPanelWidget18.SetName(n"inkVerticalPanelWidget18");
        inkVerticalPanelWidget18.SetFitToContent(true);
        inkVerticalPanelWidget18.SetHAlign(inkEHorizontalAlign.Left);
        inkVerticalPanelWidget18.SetVAlign(inkEVerticalAlign.Top);
        inkVerticalPanelWidget18.Reparent(main);

        let line: ref<inkRectangle> = new inkRectangle();
        line.SetName(n"line");
        line.SetVisible(false);
        line.SetMargin(inkMargin(174.0, 24.0, 0.0, 0.0));
        line.SetHAlign(inkEHorizontalAlign.Left);
        line.SetVAlign(inkEVerticalAlign.Top);
        line.SetAnchor(inkEAnchor.TopFillHorizontaly);
        line.SetOpacity(0.1);
        line.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        line.BindProperty(n"tintColor", n"MainColors.Red");
        line.SetSize(Vector2(3.0, 84.0));
        line.SetRenderTransformPivot(Vector2(0.0, 0.5));
        line.Reparent(inkVerticalPanelWidget18);

        let title: ref<inkText> = new inkText();
        title.SetName(n"title");
        title.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
        title.SetFontStyle(n"Semi-Bold");
        title.SetFontSize(50);
        title.SetLetterCase(textLetterCase.UpperCase);
        //title.SetWrappingInfo(new textWrappingInfo(false, 900.0, textWrappingPolicy.Default));
        title.SetAffectsLayoutWhenHidden(true);
        title.SetFitToContent(true);
        title.SetMargin(inkMargin(66.0, 20.0, 0.0, -30.0));
        title.SetVAlign(inkEVerticalAlign.Top);
        title.SetOpacity(1.0);
        title.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        title.BindProperty(n"tintColor", n"MainColors.Red");
        title.SetSize(Vector2(100.0, 32.0));
        title.Reparent(inkVerticalPanelWidget18);

        let container = new inkVerticalPanel();
        container.SetAnchor(inkEAnchor.Fill);
        container.SetMargin(inkMargin(66.0, 40.0, 20.0, 40.0));
        container.Reparent(inkVerticalPanelWidget18);

        this.m_content = main;
        this.m_title = title;

        this.SetRootWidget(main);
        this.SetContainerWidget(container);
    }

    public func GetSize() -> Vector2 {
        return this.m_content.GetSize();
    }

    public func SetTitle(text: String) {
        this.m_title.SetText(text);
    }

    public static func Create() -> ref<InMenuPopupContent> {
        let self = new InMenuPopupContent();
        self.CreateInstance();

        return self;
    }
}
