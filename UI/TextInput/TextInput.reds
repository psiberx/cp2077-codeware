// -----------------------------------------------------------------------------
// Codeware.UI.TextInput [WIP]
// -----------------------------------------------------------------------------
//
// Controls:
// - Supports most of the standard controls for text inputs
// - `Ctrl + Left` / `Ctrl + Right` to jump to the start and end
// - `Caps Lock` is currently broken in the game engine
//
// Events:
// - OnInput: Fired after text change
//
// In Progress:
// - Text Selection (Shift + Arrows)
// - Keyboard Layouts
// - Multiline Text
//

module Codeware.UI

public class TextInput extends inkCustomController {
	protected let m_root: wref<inkCanvas>;

	protected let m_viewport: wref<inkScrollArea>;

	protected let m_content: wref<inkCanvas>;

	protected let m_text: wref<inkText>;

	protected let m_caret: wref<inkRectangle>;

	protected let m_useAnimations: Bool;

	protected let m_caretBlinkAnimDef: ref<inkAnimDef>;

	protected let m_caretBlinkAnimProxy: ref<inkAnimProxy>;

	protected let m_isDisabled: Bool;

	protected let m_isHovered: Bool;

	protected let m_isFocused: Bool;

	protected let m_value: String;

	protected let m_placeholder: String;

	protected let m_maxLength: Int32;

	protected let m_caretPosition: Int32;

	protected let m_charOffsets: array<Float>;

	protected let m_isKeyDown: Bool;

	protected let m_isCharInput: Bool;

	protected let m_isHoldComplete: Bool;

	protected let m_holdFrameCount: Int32;

	protected let m_lastInput: ref<inkCharacterEvent>;

	protected let m_tickProxy: ref<inkAnimProxy>;

	protected cb func OnCreate() -> Void {
		this.m_maxLength = 4096;

		this.CreateWidgets();
		this.CreateAnimations();

		this.m_content.SetSize(this.m_caret.GetSize());
	}

	protected func CreateWidgets() -> Void {
		let root: ref<inkCanvas> = new inkCanvas();
		root.SetName(n"input");
		root.SetSize(600.0, 64.0);
		root.SetAnchor(inkEAnchor.TopLeft);
		root.SetInteractive(true);
		root.SetSupportFocus(true);

		let viewport: ref<inkScrollArea> = new inkScrollArea();
		viewport.SetName(n"viewport");
		viewport.SetAnchor(inkEAnchor.Fill);
		viewport.SetMargin(new inkMargin(8.0, 4.0, 8.0, 4.0));
		viewport.SetRenderTransformPivot(new Vector2(0.0, 0.0));
		viewport.SetFitToContentDirection(inkFitToContentDirection.Vertical);
		viewport.SetConstrainContentPosition(true);
		viewport.SetUseInternalMask(true);
		viewport.Reparent(root);

		let content: ref<inkCanvas> = new inkCanvas();
		content.SetName(n"content");
		content.SetRenderTransformPivot(new Vector2(0.0, 0.0));
		content.Reparent(viewport);

		let text: ref<inkText> = new inkText();
		text.SetName(n"text");
		text.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
		text.SetFontStyle(n"Regular");
		text.SetFontSize(42);
		text.SetTintColor(ThemeColors.Bittersweet());
		text.SetHorizontalAlignment(textHorizontalAlignment.Left);
		text.SetVerticalAlignment(textVerticalAlignment.Center);
		text.SetRenderTransformPivot(new Vector2(0.0, 0.0));
		text.Reparent(content);

		let caret: ref<inkRectangle> = new inkRectangle();
		caret.SetName(n"caret");
		caret.SetSize(new Vector2(4.0, 50.0));
		caret.SetRenderTransformPivot(new Vector2(0.0, 0.0));
		caret.Reparent(content);

		this.m_root = root;
		this.m_viewport = viewport;
		this.m_content = content;
		this.m_text = text;
		this.m_caret = caret;

		this.SetRootWidget(root);
	}

	protected func CreateAnimations() -> Void {
		let caretFadeInAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
		caretFadeInAnim.SetStartTransparency(0.0);
		caretFadeInAnim.SetEndTransparency(1.0);
		caretFadeInAnim.SetStartDelay(0.9);
		caretFadeInAnim.SetDuration(0.1);

		let caretFadeOutAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
		caretFadeOutAnim.SetStartTransparency(1.0);
		caretFadeOutAnim.SetEndTransparency(0.0);
		caretFadeOutAnim.SetStartDelay(0.4);
		caretFadeOutAnim.SetDuration(0.1);

		this.m_caretBlinkAnimDef = new inkAnimDef();
		this.m_caretBlinkAnimDef.AddInterpolator(caretFadeInAnim);
		this.m_caretBlinkAnimDef.AddInterpolator(caretFadeOutAnim);
	}

	protected cb func OnInitialize() -> Void {
		this.StartTickHandler();
		this.RegisterListeners();
		this.ApplyDisabledState();
		this.ApplyHoveredState();
		this.ApplyFocusedState();
		this.UpdateCaretState();
		this.UpdateScrollState();

		ArrayPush(this.m_charOffsets, 0.0);
	}

	protected func StartTickHandler() -> Void {
		let tickAnim: ref<inkAnimTextValueProgress> = new inkAnimTextValueProgress();
		tickAnim.SetStartProgress(0.0);
		tickAnim.SetEndProgress(0.0);
		tickAnim.SetDuration(1.0 / 60.0);

		let tickAnimDef: ref<inkAnimDef> = new inkAnimDef();
		tickAnimDef.AddInterpolator(tickAnim);

		let tickAnimOpts: inkAnimOptions;
		tickAnimOpts.loopInfinite = true;
		tickAnimOpts.loopType = inkanimLoopType.Cycle;

		this.m_tickProxy = this.m_root.PlayAnimationWithOptions(tickAnimDef, tickAnimOpts);
		this.m_tickProxy.RegisterToCallback(inkanimEventType.OnStartLoop, this, n"OnTick");
	}

	protected func RegisterListeners() -> Void {
		this.RegisterToCallback(n"OnEnter", this, n"OnHoverOver");
		this.RegisterToCallback(n"OnLeave", this, n"OnHoverOut");
		this.RegisterToCallback(n"OnFocusReceived", this, n"OnFocusReceived");
		this.RegisterToCallback(n"OnFocusLost", this, n"OnFocusLost");
		this.RegisterToCallback(n"OnRelease", this, n"OnRelease");
		this.RegisterToCallback(n"OnCharacterKey", this, n"OnCharacterKey");
	}

	protected func SetDisabledState(isDisabled: Bool) -> Void {
		if !Equals(this.m_isDisabled, isDisabled) {
			this.m_isDisabled = isDisabled;

			if this.m_isDisabled {
				this.m_isHovered = false;
				this.m_isFocused = false;
			}

			this.ApplyDisabledState();
			this.ApplyHoveredState();
			this.ApplyFocusedState();
			this.UpdateCaretState();
		}
	}

	protected func SetHoveredState(isHovered: Bool) -> Void {
		if !Equals(this.m_isHovered, isHovered) {
			this.m_isHovered = isHovered;

			if !this.m_isDisabled {
				this.ApplyHoveredState();
			}
		}
	}

	protected func SetFocusedState(isFocused: Bool) -> Void {
		if !Equals(this.m_isFocused, isFocused) {
			this.m_isFocused = isFocused;

			if !this.m_isDisabled {
				this.ApplyFocusedState();
				this.UpdateCaretState();
			}
		}
	}

	protected func ApplyDisabledState() -> Void

	protected func ApplyHoveredState() -> Void

	protected func ApplyFocusedState() -> Void

	protected func UpdateCaretState() -> Void {
		this.m_caretBlinkAnimProxy.Stop();

		if this.m_isFocused {
			let caretAnimOpts: inkAnimOptions;
			caretAnimOpts.loopInfinite = true;
			caretAnimOpts.loopType = inkanimLoopType.Cycle;

			this.m_caretBlinkAnimProxy = this.m_caret.PlayAnimationWithOptions(this.m_caretBlinkAnimDef, caretAnimOpts);
			this.m_caret.SetVisible(true);

			let fontSize: Float = Cast(this.m_text.GetFontSize());
			let caretHeight: Float = this.m_caret.GetHeight();
			let charOffset: Float = this.m_charOffsets[this.m_caretPosition];

			let caretPos: Vector2 = new Vector2(
				charOffset,
				(fontSize - caretHeight) / 2.0
			);

			this.m_caret.SetTranslation(caretPos);
		} else {
			this.m_caret.SetVisible(false);
		}
	}

	protected func UpdateScrollState() -> Void {
		let viewportSize: Vector2 = this.m_viewport.GetViewportSize();
		let contentSize: Vector2 = this.m_content.GetSize();
		let charOffset: Float = this.m_charOffsets[this.m_caretPosition];

		let scrollPos: Vector2 = this.m_content.GetTranslation();

		if contentSize.X <= viewportSize.X {
			scrollPos.X = 0.0;
		} else {
			let viewportBounds: inkMargin = new inkMargin(
				-scrollPos.X,
				0.0,
				-scrollPos.X + viewportSize.X,
				0.0
			);

			if charOffset < viewportBounds.left {
				scrollPos.X = -charOffset; // MinF(0.0
			} else {
				if charOffset > viewportBounds.right {
					scrollPos.X = -(charOffset - viewportSize.X + this.m_caret.GetWidth());
				} else {
					scrollPos.X = MaxF(scrollPos.X, -(ArrayLast(this.m_charOffsets) - viewportSize.X + this.m_caret.GetWidth()));
				}
			}
		}

		this.m_content.SetTranslation(scrollPos);
	}

	protected func TriggerInputEvent() -> Void {
		this.CallCustomCallback(n"OnInput");
	}

	protected func ProcessInputEvent(evt: ref<inkCharacterEvent>) -> Void {
		switch evt.GetType() {
			case inkCharacterEventType.CharInput:
				if !evt.IsAltDown() && !evt.IsControlDown() && !this.m_isCharInput && StrLen(this.m_value) < this.m_maxLength {
					let code: Int32 = Cast(evt.GetCharacter());
					let char: String = StrChar(code);

					switch this.m_text.GetLetterCase() {
						case textLetterCase.UpperCase:
							char = StrUpper(char);
							break;
						case textLetterCase.LowerCase:
							char = StrLower(char);
							break;
						default:
							// Caps Lock modifier is broken
							// It returns holding state, instead of locked on / off state
							if evt.IsCapsLocked() {
								char = StrUpper(char);
							}
					}

					// TODO: Layout converter

					if this.m_caretPosition == StrLen(this.m_value) {
						this.m_value += char;
					} else {
						if this.m_caretPosition == 0 {
							this.m_value = char + this.m_value;
						} else {
							this.m_value = StrLeft(this.m_value, this.m_caretPosition)
								+ char + StrRight(this.m_value, StrLen(this.m_value) - this.m_caretPosition);
						}
					}

					this.m_text.SetText(this.m_value);
					this.m_caretPosition += 1;
					this.m_isCharInput = true;
				}
				break;

			case inkCharacterEventType.Delete:
				if !this.m_isCharInput && this.m_caretPosition < StrLen(this.m_value) {
					if this.m_caretPosition == 0 {
						this.m_value = StrRight(this.m_value, StrLen(this.m_value) - 1);
					} else {
						this.m_value = StrLeft(this.m_value, this.m_caretPosition)
							+ StrRight(this.m_value, StrLen(this.m_value) - this.m_caretPosition - 1);
					}

					this.m_text.SetText(this.m_value);
					this.ProcessInputChange();
				}
				break;

			case inkCharacterEventType.Backspace:
				if !this.m_isCharInput && this.m_caretPosition > 0 {
					if this.m_caretPosition == StrLen(this.m_value) {
						this.m_value = StrLeft(this.m_value, StrLen(this.m_value) - 1);
					} else {
						if this.m_caretPosition == 1 {
							this.m_value = StrRight(this.m_value, StrLen(this.m_value) - 1);
						} else {
							this.m_value = StrLeft(this.m_value, this.m_caretPosition - 1)
								+ StrRight(this.m_value, StrLen(this.m_value) - this.m_caretPosition);
						}
					}

					this.m_text.SetText(this.m_value);
					this.m_caretPosition -= 1;
					this.ProcessInputChange();
				}
				break;

			case inkCharacterEventType.MoveCaretForward:
				if this.m_caretPosition < StrLen(this.m_value) {
					if evt.IsControlDown() {
						this.m_caretPosition = StrLen(this.m_value);
					} else {
						this.m_caretPosition += 1;
					}
					this.UpdateCaretState();
					this.UpdateScrollState();
				}
				break;

			case inkCharacterEventType.MoveCaretBackward:
				if this.m_caretPosition > 0 {
					if evt.IsControlDown() {
						this.m_caretPosition = 0;
					} else {
						this.m_caretPosition -= 1;
					}
					this.UpdateCaretState();
					this.UpdateScrollState();
				}
				break;
		}
	}

	protected func ProcessInputChange(opt diffOffset: Float) -> Void {
		if diffOffset > 0.01 {
			ArrayInsert(this.m_charOffsets, this.m_caretPosition, this.m_charOffsets[this.m_caretPosition - 1] + diffOffset);
		} else {
			diffOffset = this.m_charOffsets[this.m_caretPosition] - this.m_charOffsets[this.m_caretPosition + 1];
			ArrayErase(this.m_charOffsets, this.m_caretPosition + 1);
		}

		let lastPosition: Int32 = ArraySize(this.m_charOffsets) - 1;

		if this.m_caretPosition != lastPosition {
			let charPosition: Int32 = this.m_caretPosition + 1;

			while charPosition <= lastPosition {
				this.m_charOffsets[charPosition] += diffOffset;
				charPosition += 1;
			}
		}

		if StrLen(this.m_value) > 0 {
			this.m_content.SetWidth(this.m_content.GetWidth() + diffOffset);
		} else {
			this.m_content.SetSize(this.m_caret.GetSize());
		}

		this.UpdateCaretState();
		this.UpdateScrollState();

		this.TriggerInputEvent();
	}

	protected cb func OnHoverOver(evt: ref<inkPointerEvent>) -> Bool {
		this.SetHoveredState(true);
	}

	protected cb func OnHoverOut(evt: ref<inkPointerEvent>) -> Bool {
		this.SetHoveredState(false);
	}

	protected cb func OnFocusReceived(evt: ref<inkEvent>) -> Void {
		this.SetFocusedState(true);
	}

	protected cb func OnFocusLost(evt: ref<inkEvent>) -> Void {
		this.SetFocusedState(false);
	}

	protected cb func OnRelease(evt: ref<inkPointerEvent>) -> Bool {
		Debug("OnRelease");
		if evt.IsAction(n"mouse_left") && this.m_isFocused {
			let clickPos: Vector2 = WidgetUtils.GlobalToLocal(this.m_text, evt.GetScreenSpacePosition());

			if StrLen(this.m_value) > 0 {
				let charPosition: Int32 = 0;
				let lastPosition: Int32 = ArraySize(this.m_charOffsets) - 1;

				while charPosition < lastPosition {
					if this.m_charOffsets[charPosition] >= clickPos.X {
						break;
					}
					charPosition += 1;
				}

				this.m_caretPosition = charPosition;

				this.UpdateCaretState();
				this.UpdateScrollState();
			}
		}
	}

	protected cb func OnCharacterKey(evt: ref<inkCharacterEvent>) -> Void {
		this.m_isKeyDown = !this.m_isKeyDown;

		if this.m_isKeyDown {
			this.m_lastInput = evt;
			this.ProcessInputEvent(evt);
		} else {
			this.m_lastInput = null;
		}

		this.m_isHoldComplete = false;
		this.m_holdFrameCount = 0;
	}

	protected cb func OnTick(anim: ref<inkAnimProxy>) -> Void {
		if this.m_isCharInput {
			let lastOffset: Float = ArrayLast(this.m_charOffsets);
			let textSize: Vector2 = this.m_text.GetDesiredSize();
			let diffOffset: Float = textSize.X - lastOffset;

			if AbsF(diffOffset) > 0.01 {
				this.ProcessInputChange(diffOffset);

				this.m_isCharInput = false;
			}

			return;
		}

		if this.m_isKeyDown {
			this.m_holdFrameCount += 1;

			if this.m_holdFrameCount == (this.m_isHoldComplete ? 2 : 30) {
				this.ProcessInputEvent(this.m_lastInput);

				this.m_isHoldComplete = true;
				this.m_holdFrameCount = 0;
			}
		}
	}

	public func GetName() -> CName {
		return this.m_root.GetName();
	}

	public func SetName(name: CName) -> Void {
		this.m_root.SetName(name);
	}

	public func GetText() -> String {
		return this.m_text.GetText();
	}

	public func SetText(text: String) -> Void {
		this.m_value = text;
		this.m_text.SetText(this.m_value);

		// TODO: Calculate offsets
	}

	public func GetMaxLength() -> Int32 {
		return this.m_maxLength;
	}

	public func SetMaxLength(max: Int32) -> Void {
		this.m_maxLength = max;
	}

	public func GetLetterCase() -> textLetterCase {
		return this.m_text.GetLetterCase();
	}

	public func SetLetterCase(case: textLetterCase) -> Void {
		this.m_text.SetLetterCase(case);
	}

	public func GetCaretPosition() -> Int32 {
		return this.m_caretPosition;
	}

	public func SetCaretPosition(position: Int32) -> Void {
		position = Max(position, 0);
		position = Min(position, StrLen(this.m_value));

		if this.m_caretPosition != position {
			this.m_caretPosition = position;

			this.UpdateCaretState();
			this.UpdateScrollState();
		}
	}

	public func IsDisabled() -> Bool {
		return this.m_isDisabled;
	}

	public func SetDisabled(isDisabled: Bool) -> Void {
		this.SetDisabledState(isDisabled);
	}

	public func GetWidth() -> Float {
		return this.m_root.GetWidth();
	}

	public func SetWidth(width: Float) -> Void {
		this.m_root.SetWidth(width);
	}

	// TODO: Positioning and transformations

	public func IsEnabled() -> Bool {
		return !this.m_isDisabled;
	}

	public func IsHovered() -> Bool {
		return this.m_isHovered && !this.m_isDisabled;
	}

	public func IsFocused() -> Bool {
		return this.m_isFocused && !this.m_isDisabled;
	}

	public func ToggleAnimations(useAnimations: Bool) -> Void {
		this.m_useAnimations = useAnimations;
		this.CreateAnimations();
	}

	public static func Create() -> ref<TextInput> {
		let self: ref<TextInput> = new TextInput();
		self.CreateInstance();

		return self;
	}
}
