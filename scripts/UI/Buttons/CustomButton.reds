// -----------------------------------------------------------------------------
// Codeware.UI.CustomButton
// -----------------------------------------------------------------------------
//
// - Base implementation of custom buttons
// - Disabled / Hover / Press / Normal states
// - Custom "OnClick" event
// - Optional transition animations
// - Optional sound effects
//
// -----------------------------------------------------------------------------
//
// public abstract class CustomButton extends inkCustomController {
//   public func GetName() -> CName
//   public func GetState() -> inkEButtonState
//   public func GetText() -> String
//   public func IsEnabled() -> Bool
//   public func IsDisabled() -> Bool
//   public func IsHovered() -> Bool
//   public func IsPressed() -> Bool
//   public func SetName(name: CName)
//   public func SetText(text: String)
//   public func SetPosition(x: Float, y: Float)
//   public func SetWidth(width: Float)
//   public func SetDisabled(isDisabled: Bool)
//   public func ToggleAnimations(useAnimations: Bool)
//   public func ToggleSounds(useSounds: Bool)
// }
//

module Codeware.UI

public abstract class CustomButton extends inkCustomController {
    protected let m_root: wref<inkCompoundWidget>;
    protected let m_label: wref<inkText>;

    protected let m_useAnimations: Bool;
    protected let m_useSounds: Bool;

    protected let m_isDisabled: Bool;
    protected let m_isHovered: Bool;
    protected let m_isPressed: Bool;

    protected cb func OnCreate() {
        this.CreateWidgets();
        this.CreateAnimations();
    }

    protected cb func OnInitialize() {
        this.RegisterListeners();
        this.ApplyDisabledState();
        this.ApplyHoveredState();
    }

    protected func CreateWidgets()

    protected func CreateAnimations() {}

    protected func RegisterListeners() {
        this.RegisterToCallback(n"OnEnter", this, n"OnHoverOver");
        this.RegisterToCallback(n"OnLeave", this, n"OnHoverOut");
        this.RegisterToCallback(n"OnPress", this, n"OnPress");
        this.RegisterToCallback(n"OnRelease", this, n"OnRelease");
    }

    protected func ApplyDisabledState() {}

    protected func ApplyHoveredState() {}

    protected func ApplyPressedState() {}

    protected func SetDisabledState(isDisabled: Bool) {
        if !Equals(this.m_isDisabled, isDisabled) {
            this.m_isDisabled = isDisabled;

            if this.m_isDisabled {
                this.m_isPressed = false;
            }

            this.ApplyDisabledState();
            this.ApplyHoveredState();
            this.ApplyPressedState();
        }
    }

    protected func SetHoveredState(isHovered: Bool) {
        if !Equals(this.m_isHovered, isHovered) {
            this.m_isHovered = isHovered;

            if !this.m_isHovered {
                this.m_isPressed = false;
            }

            if !this.m_isDisabled {
                this.ApplyHoveredState();
                this.ApplyPressedState();
            }
        }
    }

    protected func SetPressedState(isPressed: Bool) {
        if !Equals(this.m_isPressed, isPressed) {
            this.m_isPressed = isPressed;

            if !this.m_isDisabled {
                this.ApplyPressedState();
            }
        }
    }

    protected cb func OnHoverOver(evt: ref<inkPointerEvent>) -> Bool {
        this.SetHoveredState(true);
    }

    protected cb func OnHoverOut(evt: ref<inkPointerEvent>) -> Bool {
        this.SetHoveredState(false);
    }

    protected cb func OnPress(evt: ref<inkPointerEvent>) -> Bool {
        if evt.IsAction(n"click") {
            this.SetPressedState(true);
        }
    }

    protected cb func OnRelease(evt: ref<inkPointerEvent>) -> Bool {
        if evt.IsAction(n"click") {
            if this.m_isPressed {
                if !this.m_isDisabled {
                    if this.m_useSounds {
                        this.PlaySound(n"Button", n"OnPress");
                    }

                    this.CallCustomCallback(n"OnBtnClick");
                }

                this.SetPressedState(false);
            }
        }
    }

    public func GetName() -> CName {
        return this.m_root.GetName();
    }

    public func GetState() -> inkEButtonState {
        if this.m_isDisabled {
            return inkEButtonState.Disabled;
        }

        if this.m_isPressed {
            return inkEButtonState.Press;
        }

        if this.m_isHovered {
            return inkEButtonState.Hover;
        }

        return inkEButtonState.Normal;
    }

    public func GetText() -> String {
        return this.m_label.GetText();
    }

    public func IsEnabled() -> Bool {
        return !this.m_isDisabled;
    }

    public func IsDisabled() -> Bool {
        return this.m_isDisabled;
    }

    public func IsHovered() -> Bool {
        return this.m_isHovered && !this.m_isDisabled;
    }

    public func IsPressed() -> Bool {
        return this.m_isPressed && !this.m_isDisabled;
    }

    public func SetName(name: CName) {
        this.m_root.SetName(name);
    }

    public func SetText(text: String) {
        this.m_label.SetText(text);
    }

    public func SetPosition(x: Float, y: Float) {
        this.m_root.SetMargin(x, y, 0, 0);
    }

    public func SetWidth(width: Float) {
        this.m_root.SetWidth(width);
    }

    public func SetDisabled(isDisabled: Bool) {
        this.SetDisabledState(isDisabled);
    }

    public func ToggleAnimations(useAnimations: Bool) {
        this.m_useAnimations = useAnimations;
        this.CreateAnimations();
    }

    public func ToggleSounds(useSounds: Bool) {
        this.m_useSounds = useSounds;
    }
}
