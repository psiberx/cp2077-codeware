// -----------------------------------------------------------------------------
// Codeware.UI.TextInput.TextFlow [WIP]
// -----------------------------------------------------------------------------

module Codeware.UI.TextInput
import Codeware.UI.inkCustomController

public class TextFlow extends inkCustomController {
    protected let m_text: wref<inkText>;

    protected let m_value: String;

    protected let m_placeholder: String;

    protected let m_length: Int32;

    protected let m_maxLength: Int32;

    protected let m_charOffsets: array<Float>;

    protected let m_tickProxy: ref<inkAnimProxy>;

    protected cb func OnCreate() {
        this.InitializeProps();
        this.CreateWidgets();
    }

    protected cb func OnInitialize() {
        this.InitializeOffsets();
        this.UpdatePlaceholder();
    }

    protected func InitializeProps() {
        this.m_maxLength = 4096;
    }

    protected func CreateWidgets() {
        let text: ref<inkText> = new inkText();
        text.SetName(n"text");
        text.SetFontFamily("base\\gameplay\\gui\\fonts\\raj\\raj.inkfontfamily");
        text.SetFontStyle(n"Regular");
        text.SetFontSize(42);
        text.SetStyle(r"base\\gameplay\\gui\\common\\main_colors.inkstyle");
        text.BindProperty(n"tintColor", n"MainColors.Red");
        text.SetHorizontalAlignment(textHorizontalAlignment.Left);
        text.SetVerticalAlignment(textVerticalAlignment.Top);
        text.SetRenderTransformPivot(Vector2(0.0, 0.0));

        this.m_text = text;

        this.SetRootWidget(text);
    }

    protected func InitializeOffsets() {
        ArrayResize(this.m_charOffsets, this.m_length + 1);

        this.m_charOffsets[0] = 0.0;

        if this.m_length > 0 {
            let position: Int32 = 1;

            while position <= this.m_length {
                this.m_charOffsets[position] = -1.0;

                position += 1;
            }
        }
    }

    protected func ProcessInsertion(position: Int32, offset: Float) {
        ArrayInsert(this.m_charOffsets, position + 1, offset);

        if offset > 0.0 {
            let diff: Float = offset - this.m_charOffsets[position - 1];

            this.UpdateFollowers(position, diff);
        }
    }

    protected func ProcessDeletion(position: Int32) {
        let diff: Float = this.m_charOffsets[position] - this.m_charOffsets[position + 1];

        ArrayErase(this.m_charOffsets, position + 1);

        this.UpdateFollowers(position, diff);
    }

    protected func ProcessDeletion(start: Int32, end: Int32) {
        let diff: Float = this.m_charOffsets[start] - this.m_charOffsets[end];

        let position: Int32 = start + 1;
        while position <= end {
            ArrayErase(this.m_charOffsets, start + 1);
            position += 1;
        }

        this.UpdateFollowers(start, diff);
    }

    protected func UpdateFollowers(position: Int32, diff: Float) {
        if position != this.m_length {
            position += 1;

            while position <= this.m_length {
                if this.m_charOffsets[position] > 0.0 {
                    this.m_charOffsets[position] += diff;
                }

                position += 1;
            }
        }
    }

    protected func UpdatePlaceholder() {
        if this.IsEmpty() {
            this.m_text.SetText(this.m_placeholder);
            this.m_text.SetOpacity(0.15);
        } else {
            this.m_text.SetOpacity(1.0);
        }
    }

    public func GetText() -> String {
        return this.m_value;
    }

    public func SetText(text: String) {
        this.m_value = text;
        this.m_length = UTF8StrLen(text);

        this.m_text.SetText(this.m_value);

        this.InitializeOffsets();
        this.UpdatePlaceholder();
    }

    public func GetDefaultText() -> String {
        return this.m_placeholder;
    }

    public func SetDefaultText(text: String) {
        this.m_placeholder = text;

        this.UpdatePlaceholder();
    }

    public func GetLength() -> Int32 {
        return this.m_length;
    }

    public func GetMaxLength() -> Int32 {
        return this.m_maxLength;
    }

    public func SetMaxLength(max: Int32) {
        this.m_maxLength = max;
    }

    public func IsEmpty() -> Bool {
        return this.m_length == 0;
    }

    public func IsFull() -> Bool {
        return this.m_length == this.m_maxLength;
    }

    public func GetLetterCase() -> textLetterCase {
        return this.m_text.GetLetterCase();
    }

    public func SetLetterCase(value: textLetterCase) {
        this.m_text.SetLetterCase(value);
    }

    public func GetFontSize() -> Int32 {
        return this.m_text.GetFontSize();
    }

    public func SetFontSize(fontSize: Int32) {
        this.m_text.SetFontSize(fontSize);
    }

    public func GetCharOffset(position: Int32) -> Float {
        if position <= 0 || position > this.m_length {
            return 0.0;
        }

        return this.m_charOffsets[position];
    }

    public func SetCharOffset(position: Int32, offset: Float) {
        if this.m_charOffsets[position] < 0.0 && offset > 0.0 {
            this.m_charOffsets[position] = offset;

            this.UpdateFollowers(position, offset - this.m_charOffsets[position - 1]);
        }
    }

    public func GetCharWidth(position: Int32) -> Float {
        if position <= 0 || position > this.m_length {
            return 0.0;
        }

        return this.m_charOffsets[position] - this.m_charOffsets[position - 1];
    }

    public func SetCharWidth(position: Int32, width: Float) {
        if this.m_charOffsets[position] < 0.0 && width > 0.0 {
            this.m_charOffsets[position] = this.m_charOffsets[position - 1] + width;

            this.UpdateFollowers(position, width);
        }
    }

    public func GetCharPosition(offset: Float) -> Int32 {
        let position: Int32 = 0;

        while position < this.m_length {
            if this.m_charOffsets[position] < 0.0 {
                return 0; // break?
            }

            if this.m_charOffsets[position] >= offset {
                break;
            }

            position += 1;
        }

        return position;
    }

    public func GetCharRange(range: RectF) -> RectF {
        return RectF(
            this.GetCharOffset(Cast(range.Left)),
            0.0,
            this.GetCharOffset(Cast(range.Right)),
            0.0
        );
    }

    public func GetNextStop(current: Int32) -> Int32 {
        return this.m_length; // FIXME
    }

    public func GetPrevStop(current: Int32) -> Int32 {
        return 0; // FIXME
    }

    public func InsertCharAt(position: Int32, char: String) {
        if this.m_length == this.m_maxLength {
            return;
        }

        position = Max(position, 0);
        position = Min(position, this.m_length);

        if position == 0 {
            this.m_value = char + this.m_value;
        } else if position == this.m_length {
            this.m_value += char;
        } else {
            this.m_value = UTF8StrLeft(this.m_value, position)
                + char + UTF8StrRight(this.m_value, this.m_length - position);
        }

        this.m_length += 1;
        this.m_text.SetText(this.m_value);

        this.ProcessInsertion(position, -1.0);
        this.UpdatePlaceholder();
    }

    public func InsertTextAt(position: Int32, text: String) {
        let length = UTF8StrLen(text);

        if this.m_length + length > this.m_maxLength {
            return;
        }

        position = Max(position, 0);
        position = Min(position, this.m_length);

        if position == 0 {
            this.m_value = text + this.m_value;
        } else if position == this.m_length {
            this.m_value += text;
        } else {
            this.m_value = UTF8StrLeft(this.m_value, position)
                + text + UTF8StrRight(this.m_value, this.m_length - position);
        }

        this.m_length += length;
        this.m_text.SetText(this.m_value);

        while length > 0 {
            this.ProcessInsertion(position, -1.0);
            position += 1;
            length -= 1;
        }

        this.UpdatePlaceholder();
    }

    public func DeleteCharAt(position: Int32) {
        position = Max(position, 0);
        position = Min(position, this.m_length - 1);

        if position == 0 {
            this.m_value = UTF8StrRight(this.m_value, this.m_length - 1);
        } else if position == this.m_length - 1 {
            this.m_value = UTF8StrLeft(this.m_value, this.m_length - 1);
        } else {
            this.m_value = UTF8StrLeft(this.m_value, position)
                + UTF8StrRight(this.m_value, this.m_length - position - 1);
        }

        this.m_length -= 1;
        this.m_text.SetText(this.m_value);

        this.ProcessDeletion(position);
        this.UpdatePlaceholder();
    }

    public func DeleteCharRange(start: Int32, end: Int32) {
        start = Max(start, 0);
        start = Min(start, this.m_length - 1);

        end = Max(end, 0);
        end = Min(end, this.m_length);

        if start == end {
            return;
        }

        this.m_value = UTF8StrLeft(this.m_value, start) + UTF8StrRight(this.m_value, this.m_length - end);
        this.m_length = UTF8StrLen(this.m_value);

        this.m_text.SetText(this.m_value);

        this.ProcessDeletion(start, end);
        this.UpdatePlaceholder();
    }

    public func GetDesiredSize() -> Vector2 {
        return Vector2(
            this.m_charOffsets[this.m_length],
            Cast(this.m_text.GetFontSize())
        );
    }

    public static func Create() -> ref<TextFlow> {
        let self: ref<TextFlow> = new TextFlow();
        self.CreateInstance();

        return self;
    }
}
