// -----------------------------------------------------------------------------
// Codeware.UI.inkCustomController
// -----------------------------------------------------------------------------
//
// public abstract class inkCustomController extends inkLogicController {
//   public func GetRootWidget() -> wref<inkWidget>
//   public func GetRootCompoundWidget() -> wref<inkCompoundWidget>
//   public func GetContainerWidget() -> wref<inkCompoundWidget>
//   public func GetGameController() -> wref<inkGameController>
//   public func GetPlayer() -> ref<PlayerPuppet>
//   public func GetGame() -> GameInstance
//   public func CallCustomCallback(eventName: CName)
//   public func RegisterToCallback(eventName: CName, object: ref<IScriptable>, functionName: CName)
//   public func UnregisterFromCallback(eventName: CName, object: ref<IScriptable>, functionName: CName)
//   public func RegisterToGlobalInputCallback(eventName: CName, object: ref<IScriptable>, functionName: CName)
//   public func UnregisterFromGlobalInputCallback(eventName: CName, object: ref<IScriptable>, functionName: CName)
//   public func PlaySound(widgetName: CName, eventName: CName, opt actionKey: CName)
//   public func Reparent(newParent: wref<inkCompoundWidget>)
//   public func Reparent(newParent: wref<inkCompoundWidget>, index: Int32)
//   public func Reparent(newParent: wref<inkCompoundWidget>, gameController: ref<inkGameController>)
//   public func Reparent(newParent: wref<inkCustomController>)
//   public func Reparent(newParent: wref<inkCustomController>, index: Int32)
//   public func Mount(rootWidget: ref<inkCompoundWidget>, opt gameController: wref<inkGameController>)
//   public func Mount(rootController: ref<inkLogicController>, opt gameController: ref<inkGameController>)
//   public func Mount(rootController: ref<inkGameController>)
//   protected cb func OnCreate()
//   protected cb func OnInitialize()
//   protected cb func OnUninitialize()
//   protected cb func OnReparent(parent: ref<inkCompoundWidget>)
//   protected func SetRootWidget(rootWidget: ref<inkWidget>)
//   protected func SetContainerWidget(containerWidget: ref<inkCompoundWidget>)
//   protected func SetGameController(gameController: ref<inkGameController>)
//   protected func SetGameController(parentController: ref<inkCustomController>)
// }
//

module Codeware.UI

public abstract class inkCustomController extends inkLogicController {
    private let m_isCreated: Bool;
    private let m_isInitialized: Bool;

    private let m_detachedWidget: ref<inkWidget>;
    private let m_gameController: wref<inkGameController>;
    private let m_pendingCallbacks: array<inkPendingCallback>;

    protected let m_rootWidget: wref<inkWidget>;
    protected let m_containerWidget: wref<inkCompoundWidget>;

    protected func IsInitialized() -> Bool {
        return this.m_isInitialized;
    }

    protected func SetRootWidget(rootWidget: ref<inkWidget>) {
        this.m_rootWidget = rootWidget;

        if IsDefined(this.m_rootWidget) {
            let controller = this.m_rootWidget.GetController();
            if !IsDefined(controller) {
                this.m_rootWidget.AttachController(this);
            } else {
                controller = this.m_rootWidget.GetControllerByType(this.GetClassName());
                if !IsDefined(controller) {
                    this.m_rootWidget.AttachController(this, true);
                }
            }

            if !inkWidgetHelper.InWindowTree(this.m_rootWidget) {
                this.m_detachedWidget = this.m_rootWidget;
            }

            if ArraySize(this.m_pendingCallbacks) > 0 {
                for callback in this.m_pendingCallbacks {
                    this.m_rootWidget.RegisterToCallback(callback.event, callback.object, callback.function);
                }
                ArrayClear(this.m_pendingCallbacks);
            }
        } else {
            this.m_detachedWidget = null;
        }
    }

    protected func ResetRootWidget() {
        this.m_rootWidget = null;
    }

    protected func SetContainerWidget(containerWidget: ref<inkCompoundWidget>) {
        this.m_containerWidget = containerWidget;
    }

    protected func SetGameController(gameController: ref<inkGameController>) {
        this.m_gameController = gameController;
    }

    protected func SetGameController(parentController: ref<inkCustomController>) {
        this.m_gameController = parentController.GetGameController();
    }

    protected func ResetGameController() {
        this.m_gameController = null;
    }

    protected func CreateInstance() {
        if !this.m_isCreated {
            this.OnCreate();
            this.CallCustomCallback(n"OnCreate");

            if IsDefined(this.m_rootWidget) {
                this.m_isCreated = true;
            }
        }
    }

    protected func InitializeInstance() {
        if this.m_isCreated && !this.m_isInitialized {
            if inkWidgetHelper.InWindowTree(this.m_rootWidget) {
                this.InitializeChildren(this.GetRootCompoundWidget());

                this.OnInitialize();
                this.CallCustomCallback(n"OnInitialize");

                this.m_isInitialized = true;
                this.m_detachedWidget = null;
            }
        }
    }

    protected func InitializeChildren(rootWidget: wref<inkCompoundWidget>) {
        if IsDefined(rootWidget) {
            let index: Int32 = 0;
            let numChildren: Int32 = rootWidget.GetNumChildren();
            let childWidget: wref<inkWidget>;
            let childControllers: array<wref<inkLogicController>>;
            let customController: wref<inkCustomController>;

            while index < numChildren {
                childWidget = rootWidget.GetWidgetByIndex(index);
                childControllers = childWidget.GetControllers();

                for childController in childControllers {
                    customController = childController as inkCustomController;

                    if IsDefined(customController) {
                        customController.SetGameController(this.GetGameController());
                        customController.InitializeInstance();
                    }
                }

                if childWidget.IsA(n"inkCompoundWidget") && !IsDefined(childWidget.GetController() as inkCustomController) {
                    this.InitializeChildren(childWidget as inkCompoundWidget);
                }

                index += 1;
            }
        }
    }

    protected cb func OnCreate() {}

    protected cb func OnInitialize() {}

    protected cb func OnUninitialize() {
        //this.m_isCreated = false;
        //this.m_isInitialized = false;
        this.m_detachedWidget = null;
    }

    protected cb func OnReparent(parent: ref<inkCompoundWidget>) {}

    public func GetRootWidget() -> wref<inkWidget> {
        return this.m_rootWidget;
    }

    public func GetRootCompoundWidget() -> wref<inkCompoundWidget> {
        return this.m_rootWidget as inkCompoundWidget;
    }

    public func GetContainerWidget() -> wref<inkCompoundWidget> {
        if IsDefined(this.m_containerWidget) {
            return this.m_containerWidget;
        }

        return this.m_rootWidget as inkCompoundWidget;
    }

    public func GetGameController() -> wref<inkGameController> {
        return this.m_gameController;
    }

    public func GetPlayer() -> ref<PlayerPuppet> {
        return this.m_gameController.GetPlayerControlledObject() as PlayerPuppet;
    }

    public func GetGame() -> GameInstance {
        return this.m_gameController.GetPlayerControlledObject().GetGame();
    }

    public func CallCustomCallback(eventName: CName) {
        if IsDefined(this.m_rootWidget) {
            this.m_rootWidget.CallCustomCallback(eventName);
        }
    }

    public func RegisterToCallback(eventName: CName, object: ref<IScriptable>, functionName: CName) {
        if IsDefined(this.m_rootWidget) {
            this.m_rootWidget.RegisterToCallback(eventName, object, functionName);
        } else {
            ArrayPush(this.m_pendingCallbacks, inkPendingCallback(eventName, object, functionName));
        }
    }

    public func UnregisterFromCallback(eventName: CName, object: ref<IScriptable>, functionName: CName) {
        if IsDefined(this.m_rootWidget) {
            this.m_rootWidget.UnregisterFromCallback(eventName, object, functionName);
        }
    }

    public func RegisterToGlobalInputCallback(eventName: CName, object: ref<IScriptable>, functionName: CName) {
        if IsDefined(this.m_gameController) {
            this.m_gameController.RegisterToGlobalInputCallback(eventName, object, functionName);
        }
    }

    public func UnregisterFromGlobalInputCallback(eventName: CName, object: ref<IScriptable>, functionName: CName) {
        if IsDefined(this.m_gameController) {
            this.m_gameController.UnregisterFromGlobalInputCallback(eventName, object, functionName);
        }
    }

    public func PlaySound(widgetName: CName, eventName: CName, opt actionKey: CName) {
        if IsDefined(this.m_gameController) {
            this.m_gameController.PlaySound(widgetName, eventName, actionKey);
        }
    }

    public func Reparent(newParent: wref<inkCompoundWidget>) {
        this.Reparent(newParent, -1);
    }

    public func Reparent(newParent: wref<inkCompoundWidget>, index: Int32) {
        this.CreateInstance();

        if IsDefined(this.m_rootWidget) && IsDefined(newParent) {
            this.m_rootWidget.Reparent(newParent, index);

            this.OnReparent(newParent);
            this.CallCustomCallback(n"OnReparent");

            this.InitializeInstance();
        }
    }

    public func Reparent(newParent: wref<inkCompoundWidget>, gameController: ref<inkGameController>) {
        if IsDefined(gameController) {
            this.SetGameController(gameController);
        }

        this.Reparent(newParent, -1);
    }

    public func Reparent(newParent: wref<inkCustomController>) {
        this.Reparent(newParent, -1);
    }

    public func Reparent(newParent: wref<inkCustomController>, index: Int32) {
        if IsDefined(newParent.GetGameController()) {
            this.SetGameController(newParent.GetGameController());
        }

        this.Reparent(newParent.GetContainerWidget(), index);
    }

    public func Mount(rootWidget: ref<inkCompoundWidget>, opt gameController: wref<inkGameController>) {
        if !this.m_isInitialized && IsDefined(rootWidget) {
            this.SetRootWidget(rootWidget);
            this.SetGameController(gameController);

            this.CreateInstance();
            this.InitializeInstance();
        }
    }

    public func Mount(rootController: ref<inkLogicController>, opt gameController: ref<inkGameController>) {
        this.Mount(rootController.GetRootCompoundWidget(), gameController);
    }

    public func Mount(rootController: ref<inkGameController>) {
        this.Mount(rootController.GetRootCompoundWidget(), rootController);
    }
}

private struct inkPendingCallback {
    let event: CName;
    let object: ref<IScriptable>;
    let function: CName;
}
