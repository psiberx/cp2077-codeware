// -----------------------------------------------------------------------------
// Codeware.UI.CustomPopup
// -----------------------------------------------------------------------------
//
// - Base implementation of custom popups
// - Close on "cancel" event (default ESC and C keys)
// - Transition animations
//
// -----------------------------------------------------------------------------
//
// public abstract class CustomPopup extends inkCustomController {
//   public func GetName() -> CName
//   public func GetQueueName() -> CName
//   public func IsBlocking() -> Bool
//   public func UseCursor() -> Bool
//   public func Open(requester: wref<inkGameController>)
//   public func Close()
//   public func Attach(rootWidget: ref<inkCanvas>, gameController: wref<inkGameController>, notificationData: ref<inkGameNotificationData>)
//   public func Detach()
// }
//

module Codeware.UI

public abstract class CustomPopup extends inkCustomController {
    protected let m_notificationData: ref<inkGameNotificationData>;
    protected let m_notificationToken: ref<inkGameNotificationToken>;
    protected let m_transitionAnimProxy: ref<inkAnimProxy>;
    protected let m_closeAction: CName;

    protected func SetNotificationData(notificationData: ref<inkGameNotificationData>) {
        this.m_notificationData = notificationData;
        this.m_notificationToken = notificationData.token;
    }

    protected func ResetNotificationData() {
        this.m_notificationToken.TriggerCallback(this.m_notificationData);
        this.m_notificationToken = null;
        this.m_notificationData = null;
    }

    protected func IsTopPopup() -> Bool {
        let popupData = this.m_notificationData as CustomPopupNotificationData;
        return !IsDefined(popupData) || popupData.manager.IsOnTop(this);
    }

    protected cb func OnInitialize() {
        super.OnInitialize();

        this.m_closeAction = n"cancel";
    }

    protected cb func OnAttach() {
        this.RegisterToGlobalInputCallback(n"OnPostOnRelease", this, n"OnGlobalReleaseInput");

        this.CallCustomCallback(n"OnShow");
        this.OnShow();
    }

    protected cb func OnDetach() {
        this.GetGameController().RequestSetFocus(null);

        this.UnregisterFromGlobalInputCallback(n"OnPostOnRelease", this, n"OnGlobalReleaseInput");

        this.CallCustomCallback(n"OnClose");
        this.CallCustomCallback(n"OnHide");
        this.OnHide();
    }

    protected cb func OnShow() {
        let alphaAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
        alphaAnim.SetStartTransparency(0.0);
        alphaAnim.SetEndTransparency(1.0);
        alphaAnim.SetType(inkanimInterpolationType.Linear);
        alphaAnim.SetMode(inkanimInterpolationMode.EasyIn);
        alphaAnim.SetDuration(0.5);

        let animDef: ref<inkAnimDef> = new inkAnimDef();
        animDef.AddInterpolator(alphaAnim);

        this.m_transitionAnimProxy = this.GetRootWidget().PlayAnimation(animDef);
        this.m_transitionAnimProxy.RegisterToCallback(inkanimEventType.OnFinish, this, n"OnShowFinish");
    }

    protected cb func OnShowFinish(animProxy: ref<inkAnimProxy>) -> Bool {
        this.m_transitionAnimProxy = null;

        this.OnShown();
        this.CallCustomCallback(n"OnShown");
    }

    protected cb func OnShown() {}

    protected cb func OnHide() {
        let alphaAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
        alphaAnim.SetStartTransparency(1.0);
        alphaAnim.SetEndTransparency(0.0);
        alphaAnim.SetType(inkanimInterpolationType.Linear);
        alphaAnim.SetMode(inkanimInterpolationMode.EasyIn);
        alphaAnim.SetDuration(0.25);

        let animDef: ref<inkAnimDef> = new inkAnimDef();
        animDef.AddInterpolator(alphaAnim);

        this.m_transitionAnimProxy = this.GetRootWidget().PlayAnimation(animDef);
        this.m_transitionAnimProxy.RegisterToCallback(inkanimEventType.OnFinish, this, n"OnHideFinish");
    }

    protected cb func OnHideFinish(animProxy: ref<inkAnimProxy>) -> Bool {
        this.m_transitionAnimProxy = null;

        this.CallCustomCallback(n"OnHidden");
        this.OnHidden();
    }

    protected cb func OnHidden() {
        this.ResetNotificationData();
        this.SetGameController(null);
        this.SetRootWidget(null);
    }

    protected cb func OnGlobalReleaseInput(evt: ref<inkPointerEvent>) -> Bool {
        if evt.IsAction(this.m_closeAction) && !evt.IsHandled() && this.IsTopPopup() {
            this.Close();
            evt.Handle();
            return true;
        }

        if this.UseCursor() && evt.IsAction(n"mouse_left") {
            if !IsDefined(evt.GetTarget()) || !evt.GetTarget().CanSupportFocus() {
                this.GetGameController().RequestSetFocus(null);
            }
        }

        return false;
    }

    public func GetName() -> CName {
        return this.GetClassName();
    }

    public func GetQueueName() -> CName {
        return n"modal_popup";
    }

    public func IsBlocking() -> Bool {
        return true;
    }

    public func UseCursor() -> Bool {
        return false;
    }

    public func Open(requester: wref<inkGameController>) {
        let uiSystem: ref<UISystem> = GameInstance.GetUISystem(requester.GetPlayerControlledObject().GetGame());
        let showEvent: ref<ShowCustomPopupEvent> = ShowCustomPopupEvent.Create(this);

        uiSystem.QueueEvent(showEvent);
    }

    public func Close() {
        let uiSystem: ref<UISystem> = GameInstance.GetUISystem(this.GetGame());
        let hideEvent: ref<HideCustomPopupEvent> = HideCustomPopupEvent.Create(this);

        uiSystem.QueueEvent(hideEvent);
    }

    public func Attach(rootWidget: ref<inkCanvas>, gameController: wref<inkGameController>, notificationData: ref<inkGameNotificationData>) {
        if !this.IsInitialized() {
            this.SetRootWidget(rootWidget);
            this.SetGameController(gameController);
            this.SetNotificationData(notificationData);

            this.CreateInstance();
            this.InitializeInstance();

            this.OnAttach();
            this.CallCustomCallback(n"OnAttach");
        }
    }

    public func Detach() {
        if this.IsInitialized() {
            this.OnDetach();
            this.CallCustomCallback(n"OnDetach");
        }
    }
}
