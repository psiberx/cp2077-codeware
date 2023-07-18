// -----------------------------------------------------------------------------
// Codeware.UI.InMenuPopup
// -----------------------------------------------------------------------------

module Codeware.UI

public abstract class InMenuPopup extends CustomPopup {
    protected let m_container: wref<inkCompoundWidget>;

    protected let m_result: GenericMessageNotificationResult;
    protected let m_confirmAction: CName;

    protected cb func OnCreate() {
        super.OnCreate();

        this.CreateVignette();
        this.CreateContainer();
    }

    protected func CreateVignette() {
        let fader = new inkRectangle();
        fader.SetName(n"fader");
        fader.SetAnchor(inkEAnchor.Fill);
        fader.SetOpacity(0.7);
        fader.SetTintColor(new HDRColor(0.027451, 0.031373, 0.039216, 1.0));
        fader.SetSize(new Vector2(64.0, 64.0));
        fader.Reparent(this.GetRootCompoundWidget());

        let bg1 = new inkImage();
        bg1.SetName(n"bg1");
        bg1.SetAtlasResource(r"base\\gameplay\\gui\\common\\masks.inkatlas");
        bg1.SetTexturePart(n"frame_gradient1");
        bg1.SetInteractive(true);
        bg1.SetHAlign(inkEHorizontalAlign.Center);
        bg1.SetVAlign(inkEVerticalAlign.Center);
        bg1.SetAnchor(inkEAnchor.Fill);
        bg1.SetAnchorPoint(new Vector2(0.5, 0.0));
        bg1.SetTintColor(new HDRColor(0.262745, 0.086275, 0.094118, 1.0));
        bg1.SetSize(new Vector2(32.0, 32.0));
        bg1.Reparent(this.GetRootCompoundWidget());

        let shadow = new inkImage();
        shadow.SetName(n"Shadow");
        shadow.SetAtlasResource(r"base\\gameplay\\gui\\common\\shadow_blobs.inkatlas");
        shadow.SetTexturePart(n"shadowBlobSquare_big");
        shadow.SetMargin(new inkMargin(0.0, 760.0, 0.0, 0.0));
        shadow.SetHAlign(inkEHorizontalAlign.Center);
        shadow.SetVAlign(inkEVerticalAlign.Center);
        shadow.SetAnchor(inkEAnchor.TopCenter);
        shadow.SetAnchorPoint(new Vector2(0.5, 0.5));
        shadow.SetTintColor(new HDRColor(0.027451, 0.031373, 0.039216, 1.0));
        shadow.SetSize(new Vector2(2500.0, 1200.0));
        shadow.Reparent(this.GetRootCompoundWidget());
    }

    protected func CreateContainer() {
        let root = this.GetRootCompoundWidget();
        root.SetAnchor(inkEAnchor.Centered);
        root.SetAnchorPoint(new Vector2(0.5, 0.5));

        let container = new inkVerticalPanel();
        container.SetName(n"container");
        container.SetInteractive(true);
        container.SetFitToContent(true);
        container.SetMargin(new inkMargin(0.0, 600.0, 0.0, 0.0));
        container.SetAnchor(inkEAnchor.TopCenter);
        container.SetAnchorPoint(new Vector2(0.5, 0.0));
        container.Reparent(this.GetRootCompoundWidget());
        
        this.m_container = container;

        this.SetContainerWidget(container);
    }

    protected cb func OnCancel()
    protected cb func OnConfirm()

    protected cb func OnInitialize() {
        super.OnInitialize();

        this.m_confirmAction = n"proceed";

        let buttons: array<ref<inkLogicController>>;
        inkWidgetHelper.GetControllersByType(this.m_container, n"Codeware.UI.PopupButton", buttons);

        for button in buttons {
            let action = (button as PopupButton).GetInputAction();
            switch action {
                case n"proceed":
                case n"proceed_popup":
                case n"one_click_confirm":
                case n"system_notification_confirm":
                case n"UI_Apply":
                    button.RegisterToCallback(n"OnBtnClick", this, n"OnConfirmClick");
                    this.m_confirmAction = action;
                    break;
                case n"cancel":
                case n"cancel_popup":
                case n"back":
                case n"UI_Cancel":
                    button.RegisterToCallback(n"OnBtnClick", this, n"OnCancelClick");
                    this.m_closeAction = action;
                    break;
            }
        }
    }

	protected cb func OnConfirmClick(widget: wref<inkWidget>) {
		this.Confirm();
	}

	protected cb func OnCancelClick(widget: wref<inkWidget>) {
		this.Cancel();
	}

    protected cb func OnGlobalReleaseInput(evt: ref<inkPointerEvent>) -> Bool {
        if evt.IsAction(this.m_closeAction) && !evt.IsHandled() && this.IsTopPopup() {
            this.Cancel();
            evt.Handle();
            return true;
        }

        if evt.IsAction(this.m_confirmAction) && !evt.IsHandled() && this.IsTopPopup() {
            this.Confirm();
            evt.Handle();
            return true;
        }

        return super.OnGlobalReleaseInput(evt);
    }

    protected func Cancel() {
        this.m_result = GenericMessageNotificationResult.Cancel;

        this.OnCancel();
        this.CallCustomCallback(n"OnCancel");

        this.Close();
    }

    protected func Confirm() {
        this.m_result = GenericMessageNotificationResult.Confirm;

        this.OnConfirm();
        this.CallCustomCallback(n"OnConfirm");

        this.Close();
    }

    public func GetQueueName() -> CName {
        return n"menu_popup";
    }

	public func UseCursor() -> Bool {
		return true;
	}

	public func GetResult() -> GenericMessageNotificationResult {
	    return this.m_result;
	}
}
