// -----------------------------------------------------------------------------
// Codeware.UI.VirtualResolutionWatcher
// -----------------------------------------------------------------------------
//
// - Watch for screen resolution changes
// - Scale and resize widgets
// - Notify controllers
//

module Codeware.UI

public class VirtualResolutionWatcher extends ConfigVarListener {
    protected let m_initialized: Bool;

    protected let m_window: Vector2;

    protected let m_game: GameInstance;

    protected let m_targets: array<ref<VirtualResolutionTarget>>;

    protected let m_gameControllers: array<wref<inkGameController>>;

    protected let m_logicControllers: array<wref<inkLogicController>>;

    public func Initialize(game: GameInstance) {
        if !this.m_initialized {
            this.m_game = game;

            if this.m_window.X == 0.0 {
                this.m_window = Vector2(3840.0, 2160.0);
            }

            this.Register(n"/video/display");

            this.ApplyScalingToAllTargets();
            this.SendEventToAllControllers();

            this.m_initialized = true;
        }
    }

    public func SetWindowSize(size: Vector2) {
        this.m_window = size;

        if this.m_initialized {
            this.ApplyScalingToAllTargets();
            this.SendEventToAllControllers();
        }
    }

    public func SetWindowSize(width: Float, height: Float) {
        this.SetWindowSize(Vector2(width, height));
    }

    public func ScaleWidget(widget: ref<inkWidget>) {
        let target = VirtualResolutionScaleTarget.Create(widget);

        ArrayPush(this.m_targets, target);

        if this.m_initialized {
            this.ApplyScalingToTarget(target);
        }
    }

    public func ResizeWidget(widget: ref<inkWidget>) {
        let target = VirtualResolutionResizeTarget.Create(widget);

        ArrayPush(this.m_targets, target);

        if this.m_initialized {
            this.ApplyScalingToTarget(target);
        }
    }

    public func NotifyController(target: ref<inkGameController>) {
        ArrayPush(this.m_gameControllers, target);

        if this.m_initialized {
            this.SendEventToController(target);
        }
    }

    public func NotifyController(target: ref<inkLogicController>) {
        ArrayPush(this.m_logicControllers, target);

        if this.m_initialized {
            this.SendEventToController(target);
        }
    }

    protected func GetCurrentState() -> ref<VirtualResolutionData> {
        let resolution = ScreenHelper.GetResolution(this.m_game);
        let size = ScreenHelper.GetScreenSize(this.m_game);
        let scale = Vector2(size.X / this.m_window.X, size.Y / this.m_window.Y);

        return VirtualResolutionData.Create(resolution, size, scale);
    }

    protected cb func OnVarModified(groupPath: CName, varName: CName, varType: ConfigVarType, reason: ConfigChangeReason) {
        if Equals(groupPath, n"/video/display") && Equals(varName, n"Resolution") && Equals(reason, ConfigChangeReason.Accepted) {
            this.ApplyScalingToAllTargets();
            this.SendEventToAllControllers();
        }
    }

    protected func ApplyScalingToAllTargets() {
        let state: ref<VirtualResolutionData> = this.GetCurrentState();

        for target in this.m_targets {
            target.ApplyState(state);
        }
    }

    protected func ApplyScalingToTarget(target: ref<VirtualResolutionTarget>) {
        target.ApplyState(this.GetCurrentState());
    }

    protected func SendEventToAllControllers() {
        let state: ref<VirtualResolutionData> = this.GetCurrentState();
        let event: ref<VirtualResolutionChangeEvent> = VirtualResolutionChangeEvent.Create(state);

        for target in this.m_gameControllers {
            target.QueueEvent(event);
        }

        for target in this.m_logicControllers {
            target.QueueEvent(event);
        }
    }

    protected func SendEventToController(target: wref<inkGameController>) {
        target.QueueEvent(VirtualResolutionChangeEvent.Create(this.GetCurrentState()));
    }

    protected func SendEventToController(target: wref<inkLogicController>) {
        target.QueueEvent(VirtualResolutionChangeEvent.Create(this.GetCurrentState()));
    }
}
