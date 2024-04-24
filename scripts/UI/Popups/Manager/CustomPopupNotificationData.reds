// -----------------------------------------------------------------------------
// Codeware.UI.CustomPopupNotificationData
// -----------------------------------------------------------------------------

module Codeware.UI

public class CustomPopupNotificationData extends inkGameNotificationData {
    public let controller: ref<CustomPopup>;
    public let manager: wref<CustomPopupManager>;
}
