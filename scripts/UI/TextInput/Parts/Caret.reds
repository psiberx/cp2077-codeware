// -----------------------------------------------------------------------------
// Codeware.UI.TextInput.Caret [WIP]
// -----------------------------------------------------------------------------

module Codeware.UI.TextInput
import Codeware.UI.inkCustomController

public class Caret extends inkCustomController {
    protected let m_caret: wref<inkRectangle>;

    protected let m_position: Int32;

    protected let m_maxPosition: Int32;

    protected let m_opacity: Float;

    protected let m_fontSize: Float;

    protected let m_padSize: Float;

    protected let m_blinkAnimDef: ref<inkAnimDef>;

    protected let m_blinkAnimProxy: ref<inkAnimProxy>;

    protected cb func OnCreate() {
        this.InitializeProps();
        this.CreateWidgets();
        this.CreateAnimations();
    }

    protected cb func OnInitialize() {
        this.InitializeLayout();
    }

    protected func InitializeProps() {
        this.m_opacity = 0.9;
        this.m_padSize = 6.0;
    }

    protected func CreateWidgets() {
        let caret: ref<inkRectangle> = new inkRectangle();
        caret.SetName(n"caret");
        caret.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        caret.BindProperty(n"tintColor", n"MainColors.White");
        caret.SetRenderTransformPivot(Vector2(0.0, 0.0));

        this.m_caret = caret;

        this.SetRootWidget(this.m_caret);
    }

    protected func CreateAnimations() {
        let fadeInAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
        fadeInAnim.SetStartTransparency(0.0);
        fadeInAnim.SetEndTransparency(this.m_opacity);
        fadeInAnim.SetStartDelay(0.9);
        fadeInAnim.SetDuration(0.1);

        let fadeOutAnim: ref<inkAnimTransparency> = new inkAnimTransparency();
        fadeOutAnim.SetStartTransparency(this.m_opacity);
        fadeOutAnim.SetEndTransparency(0.0);
        fadeOutAnim.SetStartDelay(0.4);
        fadeOutAnim.SetDuration(0.1);

        this.m_blinkAnimDef = new inkAnimDef();
        this.m_blinkAnimDef.AddInterpolator(fadeInAnim);
        this.m_blinkAnimDef.AddInterpolator(fadeOutAnim);
    }

    protected func InitializeLayout() {
        this.m_caret.SetSize(Vector2(4.0, this.m_fontSize + this.m_padSize * 2.0));
    }

    public func GetFontSize() -> Int32 {
        return Cast(this.m_fontSize);
    }

    public func SetFontSize(fontSize: Int32) {
        this.m_fontSize = Cast(fontSize);

        this.InitializeLayout();
    }

    public func GetTintColor() -> HDRColor {
        return this.m_caret.GetTintColor();
    }

    public func SetTintColor(color: HDRColor) {
        this.m_caret.SetTintColor(color);
    }

    public func GetOpacity() -> Float {
        return this.m_opacity;
    }

    public func SetOpacity(opacity: Float) {
        this.m_opacity = opacity;
    }

    public func GetMaxPosition() -> Int32 {
        return this.m_maxPosition;
    }

    public func SetMaxPosition(max: Int32) {
        this.m_maxPosition = max;
    }

    public func GetPosition() -> Int32 {
        return this.m_position;
    }

    public func SetPosition(position: Int32) {
        position = Max(position, 0);
        position = Min(position, this.m_maxPosition);

        this.m_position = position;
    }

    public func AdjustPosition(diff: Int32) {
        this.SetPosition(this.m_position + diff);
    }

    public func MoveToNextChar() {
        this.SetPosition(this.m_position + 1);
    }

    public func MoveToPrevChar() {
        this.SetPosition(this.m_position - 1);
    }

    public func MoveToEnd() {
        this.SetPosition(this.m_maxPosition);
    }

    public func MoveToStart() {
        this.SetPosition(0);
    }

    public func IsAt(position: Int32) -> Bool {
        return this.m_position == position;
    }

    public func IsAtStart() -> Bool {
        return this.m_position == 0;
    }

    public func IsAtEnd() -> Bool {
        return this.m_position == this.m_maxPosition;
    }

    public func UpdateState(isFocused: Bool, caretOffset: Float) {
        this.m_blinkAnimProxy.Stop();

        if isFocused {
            let caretAnimOpts: inkAnimOptions;
            caretAnimOpts.loopInfinite = true;
            caretAnimOpts.loopType = inkanimLoopType.Cycle;

            this.m_blinkAnimProxy = this.m_caret.PlayAnimationWithOptions(this.m_blinkAnimDef, caretAnimOpts);
            this.m_caret.SetVisible(true);

            let caretPos = Vector2(
                caretOffset,
                (this.m_fontSize - this.m_caret.GetHeight()) / 2.0
            );

            this.m_caret.SetTranslation(caretPos);
        } else {
            this.m_caret.SetVisible(false);
        }
    }

    public func GetSize() -> Vector2 {
        return this.m_caret.GetSize();
    }

    public static func Create(/*offsetProvider: ref<IOffsetProvider>*/) -> ref<Caret> {
        let self: ref<Caret> = new Caret();
        self.CreateInstance();

        return self;
    }
}
