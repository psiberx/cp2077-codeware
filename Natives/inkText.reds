// -----------------------------------------------------------------------------
// inkText
// -----------------------------------------------------------------------------
//
// - Content alignment options
// - Justification options
// - Overflow policy
// - Line height
//
// -----------------------------------------------------------------------------
//
// class inkText extends inkLeafWidget {
//   public func GetContentHAlign() -> inkEHorizontalAlign
//   public func SetContentHAlign(contentHAlign: inkEHorizontalAlign) -> Void
//   public func GetContentVAlign() -> inkEVerticalAlign
//   public func SetContentVAlign(contentVAlign: inkEVerticalAlign) -> Void
//   public func GetJustificationType() -> textJustificationType
//   public func SetJustificationType(justificationType: textJustificationType) -> Void
//   public func GetOverflowPolicy() -> textOverflowPolicy
//   public func SetOverflowPolicy(overflowPolicy: textOverflowPolicy) -> Void
//   public func GetLineHeight() -> Float
//   public func SetLineHeight(lineHeight: Float) -> Void
// }
//
import Codeware.StringUtils.*

@addField(inkText)
native let contentHAlign: inkEHorizontalAlign;

@addField(inkText)
native let contentVAlign: inkEVerticalAlign;

@addField(inkText)
native let justification: textJustificationType;

@addField(inkText)
native let textOverflowPolicy: textOverflowPolicy;

@addField(inkText)
native let lineHeightPercentage: Float;

@addField(inkText)
private let simpleWrapPosition: Float;

@addMethod(inkText)
public func GetContentHAlign() -> inkEHorizontalAlign {
	return this.contentHAlign;
}

@addMethod(inkText)
public func SetContentHAlign(contentHAlign: inkEHorizontalAlign) -> Void {
	this.contentHAlign = contentHAlign;
}

@addMethod(inkText)
public func GetContentVAlign() -> inkEVerticalAlign {
	return this.contentVAlign;
}

@addMethod(inkText)
public func SetContentVAlign(contentVAlign: inkEVerticalAlign) -> Void {
	this.contentVAlign = contentVAlign;
}

@addMethod(inkText)
public func GetJustificationType() -> textJustificationType {
	return this.justification;
}

@addMethod(inkText)
public func SetJustificationType(justificationType: textJustificationType) -> Void {
	this.justification = justificationType;
}

@addMethod(inkText)
public func GetOverflowPolicy() -> textOverflowPolicy {
	return this.textOverflowPolicy;
}

@addMethod(inkText)
public func SetOverflowPolicy(overflowPolicy: textOverflowPolicy) -> Void {
	this.textOverflowPolicy = overflowPolicy;
}

@addMethod(inkText)
public func GetLineHeight() -> Float {
	return this.lineHeightPercentage;
}

@addMethod(inkText)
public func SetLineHeight(lineHeight: Float) -> Void {
	this.lineHeightPercentage = lineHeight;
}

@addMethod(inkText)
public func SetSimpleWrapPosition(wrapPosition: Float) -> Void {
	this.simpleWrapPosition = wrapPosition;
}

@addMethod(inkText)
public func GetSimpleWrapPosition() -> Float {
	return this.simpleWrapPosition;
}

@addMethod(inkText)
public func SetTextAndWrap(text: String) -> String {
	let SPLIT_CHARS = [" ", "-", "\t"];

	// Very rough calculation of the letter width (not actual pixel length, but generally close enough)
	let letterHeight = Cast<Float>(this.GetFontSize());
	let letterWidth = Cast<Float>(this.GetFontSize()) / 2.0;

	// Use the set width if no wrap position is specified
	let wrapPosition = (this.GetSimpleWrapPosition() > 0.0) ? this.GetSimpleWrapPosition() : this.GetWidth();

	let words: array<String> = SplitWords(text, SPLIT_CHARS);
	let wrappedString: String = "";

	let currentLineLength = 0.0;
	let i = 0;
	while (i < ArraySize(words)) {
		let word = words[i];
		let wordWidth = Cast<Float>(StrLen(word)) * letterWidth;

		if ((currentLineLength + wordWidth) > wrapPosition) {
			if (currentLineLength > 0.0) {
				wrappedString += "\n";
				currentLineLength = 0.0;
			}

			while(wordWidth > wrapPosition) {
				let splitIndex: Int32 = Cast<Int32>(wrapPosition / letterWidth) - 1;
				wrappedString += StrMid(word, 0, splitIndex) + "-";

				word = StrMid(word, splitIndex);
				wordWidth = Cast<Float>(StrLen(word)) * letterWidth;
				wrappedString += "\n";
			}
			word = StrTrimStart(word);
		}

		wrappedString += word;
		currentLineLength += wordWidth;
		i += 1;
	}
	this.SetText(wrappedString);
}

//var lockFontInGame : Bool; // 0x2bc
//var wrappingInfo : textWrappingInfo; // 0x328
//struct textWrappingInfo
//{
//	var autoWrappingEnabled : Bool; // 0
//	var wrappingAtPosition : Float; // 0x4
//	var wrappingPolicy : textWrappingPolicy; // 0x8
//}
//enum textWrappingPolicy
//{
//	Default = 0,
//	PerCharacter = 1
//}
