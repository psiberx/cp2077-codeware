module Codeware.UI

@addField(GenericMessageNotificationData)
public let params: ref<inkTextParams>;

@addField(GenericMessageNotificationData)
public let isInput: Bool;

@addField(GenericMessageNotificationCloseData)
public let input: String;

@addField(GenericMessageNotification)
public let m_textInput: ref<TextInput>;

@addMethod(GenericMessageNotification)
public final static func Show(controller: ref<worlduiIGameController>, title: String, message: String, params: ref<inkTextParams>, type: GenericMessageNotificationType) -> ref<inkGameNotificationToken> {
    let data = GenericMessageNotification.GetBaseData();
    data.title = title;
    data.message = message;
    data.params = params;
    data.type = type;

    return controller.ShowGameNotification(data);
}

@addMethod(GenericMessageNotification)
public final static func ShowInput(controller: ref<worlduiIGameController>, title: String, message: String, type: GenericMessageNotificationType) -> ref<inkGameNotificationToken> {
    let data = GenericMessageNotification.GetBaseData();
    data.title = title;
    data.message = message;
    data.type = type;
    data.isInput = true;

    return controller.ShowGameNotification(data);
}

@wrapMethod(GenericMessageNotification)
protected cb func OnInitialize() -> Bool {
    wrappedMethod();

    if IsDefined(this.m_data.params) {
        inkTextRef.SetText(this.m_message, this.m_data.message, this.m_data.params);
    }

    if this.m_data.isInput {
        let content = this.GetChildWidgetByPath(n"notification/main/inkVerticalPanelWidget18") as inkCompoundWidget;
        let line = this.GetChildWidgetByPath(n"notification/main/inkVerticalPanelWidget18/line");
        let title = this.GetChildWidgetByPath(n"notification/main/inkVerticalPanelWidget18/title");
        let icon = this.GetChildWidgetByPath(n"notification/main/warning_icon");

        this.m_textInput = HubTextInput.Create();
        this.m_textInput.SetName(n"TextInput");
        this.m_textInput.SetLetterCase(textLetterCase.UpperCase);
        this.m_textInput.Reparent(content);

        let textWidget = this.m_textInput.GetRootWidget();
        textWidget.SetMargin(inkMargin(66.0, 4.0, 50.0, 36.0));

        this.RequestSetFocus(textWidget);

        icon.SetVisible(false);
        line.SetVisible(false);
        title.SetMargin(inkMargin(66.0, 20.0, 0.0, -30.0));
    }
}

@replaceMethod(GenericMessageNotification)
private final func Close(result: GenericMessageNotificationResult) -> Void {
    this.m_closeData = new GenericMessageNotificationCloseData();
    this.m_closeData.identifier = this.m_data.identifier;
    this.m_closeData.result = result;

    if this.m_data.isInput {
        this.m_closeData.input = this.m_textInput.GetText();
    }

    this.PlayLibraryAnimation(n"outro");

    this.m_data.token.TriggerCallback(this.m_closeData);
}

@wrapMethod(GenericMessageNotification)
protected cb func OnHandlePressInput(evt: ref<inkPointerEvent>) -> Bool {
    wrappedMethod(evt);

    if evt.IsAction(n"click") {
        if !IsDefined(evt.GetTarget()) || !evt.GetTarget().CanSupportFocus() {
            this.RequestSetFocus(null);
        }
    }
}
