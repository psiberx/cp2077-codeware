// -----------------------------------------------------------------------------
// Codeware.UI.ButtonHintsEx
// -----------------------------------------------------------------------------
//
// - Alternative styles (popup)
// - Lock state to temporarily prevent updates
// - [TODO] Update hint visibility without removing it
//

module Codeware.UI

public class ButtonHintsEx extends inkCustomController {
    private let m_buttonHints: wref<ButtonHints>;

    private let m_isLocked: Bool;

    private let m_style: CName;

    public func AddButtonHint(action: CName, label: CName, holdInteraction: Bool) {
        if !this.m_isLocked {
            this.m_buttonHints.AddButtonHint(action, label, holdInteraction);

            if NotEquals(this.m_style, n"") {
                this.ApplyItemStyle(this.m_buttonHints.CheckForPreExisting(action));
            }
        }
    }

    public func AddButtonHint(action: CName, label: CName) {
        if !this.m_isLocked {
            this.m_buttonHints.AddButtonHint(action, label);

            if NotEquals(this.m_style, n"") {
                this.ApplyItemStyle(this.m_buttonHints.CheckForPreExisting(action));
            }
        }
    }

    public func AddButtonHint(action: CName, label: String) {
        if !this.m_isLocked {
            this.m_buttonHints.AddButtonHint(action, label);

            if NotEquals(this.m_style, n"") {
                this.ApplyItemStyle(this.m_buttonHints.CheckForPreExisting(action));
            }
        }
    }

    public func AddCharacterRoatateButtonHint() {
        if !this.m_isLocked {
            this.m_buttonHints.AddCharacterRoatateButtonHint();

            if NotEquals(this.m_style, n"") {
                this.ApplyLastItemStyle();
            }
        }
    }

    public func RemoveButtonHint(action: CName) {
        if !this.m_isLocked {
            this.m_buttonHints.RemoveButtonHint(action);
        }
    }

    public func ClearButtonHints() {
        if !this.m_isLocked {
            this.m_buttonHints.ClearButtonHints();
        }
    }

    public func Show() {
        this.m_buttonHints.Show();
    }

    public func Hide() {
        this.m_buttonHints.Hide();
    }

    public func IsVisible() -> Bool {
        return this.m_buttonHints.IsVisible();
    }

    public func Lock() {
        this.m_isLocked = true;
    }

    public func Unlock() {
        this.m_isLocked = false;
    }

    public func IsLocked() -> Bool {
        return this.m_isLocked;
    }

    public func SetStyle(styleName: CName) {
        this.m_style = styleName;

        this.ApplyListStyle();
    }

    private func ApplyListStyle() {
        let holder = inkWidgetRef.Get(this.m_buttonHints.m_horizontalHolder) as inkCompoundWidget;

        if Equals(this.m_style, n"popup") {
            holder.SetChildMargin(inkMargin(30.0, 0.0, 0.0, 0.0));
        } else {
            holder.SetChildMargin(inkMargin(0.0, 0.0, 0.0, 0.0));
        }
    }

    private func ApplyItemStyle(item: ref<ButtonHintListItem>) {
        if Equals(this.m_style, n"popup") {
            let label: wref<inkText> = item.GetWidget(n"holder/label") as inkText;

            if !IsDefined(label) {
                label = item.GetWidget(n"inputDisplayController/label") as inkText;
            }

            label.SetFontSize(38);
            label.SetFontStyle(n"Semi-Bold");
            label.SetLetterCase(textLetterCase.UpperCase);
        }
    }

    private func ApplyLastItemStyle() {
        let holder = inkWidgetRef.Get(this.m_buttonHints.m_horizontalHolder) as inkCompoundWidget;

        this.ApplyItemStyle(holder.GetWidgetByIndex(holder.GetNumChildren() - 1).GetController() as ButtonHintListItem);
    }

    public static func Wrap(root: ref<inkWidget>) -> ref<ButtonHintsEx> {
        let buttonHints: ref<ButtonHints> = root.GetController() as ButtonHints;

        if !IsDefined(buttonHints) {
            return null;
        }

        let self: ref<ButtonHintsEx> = new ButtonHintsEx();
        self.m_buttonHints = buttonHints;
        self.Mount(root as inkCompoundWidget);

        return self;
    }
}
