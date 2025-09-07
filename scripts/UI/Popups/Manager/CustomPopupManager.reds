// -----------------------------------------------------------------------------
// Codeware.UI.CustomPopupManager
// -----------------------------------------------------------------------------
//
// public class CustomPopupManager {
//   public func IsInitialized() -> Bool
//   public func Initialize(controller: ref<inkGameController>)
//   public func ShowPopup(popupController: ref<CustomPopup>)
//   public func HidePopup(popupController: ref<CustomPopup>)
//   public func AttachPopup(request: ref<CustomPopupAttachRequest>)
//   public static func GetInstance(game: GameInstance) -> ref<CustomPopupManager>
// }
//

module Codeware.UI

public class CustomPopupManager extends ScriptableService {
    private let m_gameController: wref<inkGameController>;
    private let m_notificationsContainer: wref<inkCompoundWidget>;
    private let m_bracketsContainer: wref<inkCompoundWidget>;
    private let m_notificationQueues: array<CName>;

    public func IsInitialized() -> Bool {
        return IsDefined(this.m_gameController);
    }

    public func Initialize(controller: ref<inkGameController>) {
        this.m_gameController = controller;
        this.m_notificationsContainer = this.m_gameController.GetChildWidgetByPath(n"NotificationsContainer") as inkCompoundWidget;
        this.m_bracketsContainer = this.m_gameController.GetChildWidgetByPath(n"BracketsContainer") as inkCompoundWidget;

        this.m_notificationsContainer.SetChildOrder(inkEChildOrder.Forward);
    }

    public func ShowPopup(popupController: ref<CustomPopup>) {
        if !this.IsInitialized() || !IsDefined(popupController) {
            return;
        }

        if ArrayContains(this.m_notificationQueues, popupController.GetQueueName()) {
            return;
        }

        let notificationData = new CustomPopupNotificationData();
        notificationData.manager = this;
        notificationData.controller = popupController;
        notificationData.notificationName = popupController.GetName();
        notificationData.queueName = popupController.GetQueueName();
        notificationData.isBlocking = popupController.IsBlocking();
        notificationData.useCursor = popupController.UseCursor();

        ArrayPush(this.m_notificationQueues, notificationData.queueName);

        let notificationToken = this.m_gameController.ShowGameNotification(notificationData);

        this.QueueAttachRequest(
            CustomPopupAttachRequest.Create(
                popupController,
                notificationData,
                notificationToken,
                ArraySize(this.m_notificationQueues) - 1
            )
        );
    }

    public func AttachPopup(request: ref<CustomPopupAttachRequest>) {
        let containerWidget = this.m_notificationsContainer.GetWidget(request.GetQueueIndex()) as inkCompoundWidget;

        if !IsDefined(containerWidget) {
            this.QueueAttachRequest(request);
            return;
        }

        let popupController = request.GetPopupController();
        let notificationData = request.GetNotificationData();
        let notificationToken = request.GetNotificationToken();

        let wrapperWidget = new inkCanvas();
        wrapperWidget.SetName(popupController.GetName());
        wrapperWidget.SetAnchor(inkEAnchor.Fill);
        wrapperWidget.SetAnchorPoint(Vector2(0.5, 0.5));
        wrapperWidget.SetSize(this.m_notificationsContainer.GetSize());
        wrapperWidget.Reparent(containerWidget);

        let rootWidget = new inkCanvas();
        rootWidget.SetName(n"Root");
        rootWidget.SetAnchor(this.m_bracketsContainer.GetAnchor());
        rootWidget.SetAnchorPoint(this.m_bracketsContainer.GetAnchorPoint());
        rootWidget.SetSize(this.m_bracketsContainer.GetSize());
        rootWidget.SetScale(this.m_bracketsContainer.GetScale());
        rootWidget.Reparent(wrapperWidget);

        popupController.Attach(rootWidget, this.m_gameController, notificationData);

        notificationToken.RegisterListener(this, n"OnNotificationClosed");
    }

    public func HidePopup(popupController: ref<CustomPopup>) {
        if IsDefined(popupController) {
            popupController.Detach();
        }
    }

    protected func QueueAttachRequest(request: ref<CustomPopupAttachRequest>) {
        let game = this.m_gameController.GetPlayerControlledObject().GetGame();

        GameInstance.GetDelaySystem(game).DelayCallback(CustomPopupAttachCallback.Create(this, request), 0);
    }

    protected cb func OnNotificationClosed(data: ref<inkGameNotificationData>) -> Bool {
        let notificationData = data as CustomPopupNotificationData;
        let popupController = notificationData.controller;

        ArrayRemove(this.m_notificationQueues, notificationData.queueName);

        if IsDefined(popupController) {
            let wrapperWidget = this.m_notificationsContainer.GetWidgetByPathName(popupController.GetName()) as inkCanvas;

            if IsDefined(wrapperWidget) {
                this.m_notificationsContainer.RemoveChild(wrapperWidget);
            }
        }
    }

    public func IsOnTop(popupController: ref<CustomPopup>) -> Bool {
        let topWidget = this.m_notificationsContainer.GetWidget(this.m_notificationsContainer.GetNumChildren() - 1);
        let popupWidget = popupController.GetRootWidget().GetParentWidget().GetParentWidget();

        return Equals(topWidget, popupWidget);
    }

    public static func GetInstance() -> ref<CustomPopupManager> {
        return GameInstance.GetScriptableServiceContainer()
            .GetService(n"Codeware.UI.CustomPopupManager") as CustomPopupManager;
    }
}

// -----------------------------------------------------------------------------

@wrapMethod(PopupsManager)
protected cb func OnPlayerAttach(playerPuppet: ref<GameObject>) -> Bool {
    wrappedMethod(playerPuppet);

    CustomPopupManager.GetInstance().Initialize(this);
}

@addMethod(PopupsManager)
protected cb func OnShowCustomPopup(evt: ref<ShowCustomPopupEvent>) -> Bool {
    CustomPopupManager.GetInstance().ShowPopup(evt.GetPopupController());
}

@addMethod(PopupsManager)
protected cb func OnHideCustomPopup(evt: ref<HideCustomPopupEvent>) -> Bool {
    CustomPopupManager.GetInstance().HidePopup(evt.GetPopupController());
}
