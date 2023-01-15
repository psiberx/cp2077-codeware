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

@addField(inkText)
native let contentHAlign: inkEHorizontalAlign;

@addField(inkText)
native let contentVAlign: inkEVerticalAlign;

@addField(inkText)
native let justification: textJustificationType;

@addField(inkText)
native let textOverflowPolicy: textOverflowPolicy;

@addField(inkText)
native let wrappingInfo: textWrappingInfo;

@addField(inkText)
native let lineHeightPercentage: Float;

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
public func SetWrapping(enabled: Bool, opt width: Float, opt policy: textWrappingPolicy) -> Void {
	this.wrappingInfo.autoWrappingEnabled = enabled;
	this.wrappingInfo.wrappingAtPosition = width;
	this.wrappingInfo.wrappingPolicy = policy;
}

@addMethod(inkText)
public func GetLineHeight() -> Float {
	return this.lineHeightPercentage;
}

@addMethod(inkText)
public func SetLineHeight(lineHeight: Float) -> Void {
	this.lineHeightPercentage = lineHeight;
}
