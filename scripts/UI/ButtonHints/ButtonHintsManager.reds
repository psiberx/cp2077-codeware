// -----------------------------------------------------------------------------
// Codeware.UI.ButtonHintsManager
// -----------------------------------------------------------------------------
//
// public class ButtonHintsManager {
//   public func IsInitialized() -> Bool
//   public func Initialize(buttonHints: ref<inkWidget>)
//   public func SpawnButtonHints(parentWidget: wref<inkWidget>) -> ref<ButtonHintsEx>
//   public static func GetInstance(game: GameInstance) -> ref<ButtonHintsManager>
// }
//

module Codeware.UI

public class ButtonHintsManager extends ScriptableService {
    private let m_buttonHints: ref<inkWidget>;
    private let m_inputHint: wref<inkInputDisplayController>;

    private cb func OnUninitialize() {
        this.m_buttonHints = null;
        this.m_inputHint = null;
    }

    public func IsInitialized() -> Bool {
        return IsDefined(this.m_buttonHints);
    }

    public func Initialize(buttonHints: ref<inkWidget>) {
        this.m_buttonHints = buttonHints;
    }

    public func Initialize(buttonHints: ref<ButtonHints>) {
        this.m_buttonHints = buttonHints.GetRootWidget();
    }

    public func Initialize(parent: ref<inkGameController>) {
        let rootWidget = parent.GetRootCompoundWidget();
        let buttonHints = parent.SpawnFromExternal(rootWidget, r"base\\gameplay\\gui\\common\\buttonhints.inkwidget", n"Root");

        this.Initialize(buttonHints);

        rootWidget.RemoveChild(buttonHints);
    }

    public func SpawnButtonHints(parentWidget: wref<inkWidget>) -> ref<ButtonHintsEx> {
        return ButtonHintsEx.Wrap(
            this.m_buttonHints.GetController().SpawnFromLocal(parentWidget, n"Root")
        );
    }

    public func GetActionKey(action: CName) -> String {
        if !IsDefined(this.m_inputHint) {
            let buttonHints = this.m_buttonHints.GetController() as ButtonHints;
            buttonHints.ClearButtonHints();
            buttonHints.AddButtonHint(action, "");

            this.m_inputHint = buttonHints.CheckForPreExisting(action).m_buttonHint;
        }

        this.m_inputHint.SetInputAction(action);

        let icon = this.m_inputHint.GetWidget(n"inputRoot/inputIcon") as inkImage;
        let part = icon.GetTexturePart();
        let key = NameToString(part);

        return key;
    }

    public static func GetInstance() -> ref<ButtonHintsManager> {
        return GameInstance.GetScriptableServiceContainer()
            .GetService(n"Codeware.UI.ButtonHintsManager") as ButtonHintsManager;
    }

    public static func InitializeFromController(controller: ref<inkGameController>) {
        ButtonHintsManager.GetInstance().Initialize(controller);
    }
}

// -----------------------------------------------------------------------------

@wrapMethod(SingleplayerMenuGameController)
protected cb func OnInitialize() -> Bool {
    wrappedMethod();

    ButtonHintsManager.InitializeFromController(this);
}

@wrapMethod(DpadWheelGameController)
protected cb func OnInitialize() -> Bool {
    wrappedMethod();

    ButtonHintsManager.InitializeFromController(this);
}
