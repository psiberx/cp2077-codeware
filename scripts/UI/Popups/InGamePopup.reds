// -----------------------------------------------------------------------------
// Codeware.UI.InGamePopup
// -----------------------------------------------------------------------------
//
// - Base class for in-game custom popups
// - Adds standard vignette as seen in original popups
// - Adds container widget centered on screen by default
// - Sets the appropriate UI context so that the game and other mods know
//   that the modal popup is currently active
// - Sets the time dilation as for original modal popups
// - Blurs the screen as for original modal popups
//

module Codeware.UI

public abstract class InGamePopup extends CustomPopup {
    protected let m_vignette: wref<inkImage>;
    protected let m_container: wref<inkCompoundWidget>;

    protected cb func OnCreate() {
        super.OnCreate();

        this.CreateVignette();
        this.CreateContainer();
    }

    protected func CreateVignette() {
        let vignette: ref<inkImage> = new inkImage();
        vignette.SetName(n"vignette");
        vignette.SetAtlasResource(r"base\\gameplay\\gui\\widgets\\notifications\\vignette.inkatlas");
        vignette.SetTexturePart(n"vignette_1");
        vignette.SetNineSliceScale(true);
        vignette.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        vignette.BindProperty(n"tintColor", n"MainColors.Red");
        vignette.SetSize(32.0, 32.0);
        vignette.SetAnchor(inkEAnchor.CenterFillHorizontaly);
        vignette.SetAnchorPoint(Vector2(0.5, 0.5));
        vignette.SetHAlign(inkEHorizontalAlign.Center);
        vignette.SetVAlign(inkEVerticalAlign.Center);
        vignette.SetFitToContent(true);
        vignette.Reparent(this.GetRootCompoundWidget());

        this.m_vignette = vignette;
    }

    protected func CreateContainer() {
        let container: ref<inkCanvas> = new inkCanvas();
        container.SetName(n"container");
        container.SetMargin(inkMargin(0.0, 0.0, 0.0, 200.0));
        container.SetAnchor(inkEAnchor.Centered);
        container.SetAnchorPoint(Vector2(0.5, 0.5));
        container.SetSize(Vector2(1550.0, 840.0));
        container.Reparent(this.GetRootCompoundWidget());

        this.m_container = container;

        this.SetContainerWidget(container);
    }

    protected cb func OnShow() {
        super.OnShow();

        this.SetUIContext();
        this.SetTimeDilation();
        this.SetBackgroundBlur();
        this.PlayShowSound();
    }

    protected cb func OnHide() {
        super.OnHide();

        this.ResetUIContext();
        this.ResetTimeDilation();
        this.ResetBackgroundBlur();
        this.PlayHideSound();
    }

    protected func SetTimeDilation() {
        TimeDilationHelper.SetTimeDilationWithProfile(this.GetPlayer(), "radialMenu", true, true);
    }

    protected func ResetTimeDilation() {
        TimeDilationHelper.SetTimeDilationWithProfile(this.GetPlayer(), "radialMenu", false, false);
    }

    protected func SetBackgroundBlur() {
        PopupStateUtils.SetBackgroundBlur(this.m_gameController, true);
    }

    protected func ResetBackgroundBlur() {
        PopupStateUtils.SetBackgroundBlur(this.m_gameController, false);
    }

    protected func SetUIContext() {
        let uiSystem: ref<UISystem> = GameInstance.GetUISystem(this.GetGame());
        uiSystem.PushGameContext(UIGameContext.ModalPopup);
        uiSystem.RequestNewVisualState(n"inkModalPopupState");
    }

    protected func ResetUIContext() {
        let uiSystem: ref<UISystem> = GameInstance.GetUISystem(this.GetGame());
        uiSystem.PopGameContext(UIGameContext.ModalPopup);
        uiSystem.RestorePreviousVisualState(n"inkModalPopupState");
    }

    protected func PlayShowSound() {
        //this.PlaySound(n"RadialMenu", n"OnOpen");
    }

    protected func PlayHideSound() {
        //this.PlaySound(n"RadialMenu", n"OnClose");
    }

    public func GetQueueName() -> CName {
        return n"game_popup";
    }
}
