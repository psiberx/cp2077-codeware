// -----------------------------------------------------------------------------
// inkText
// -----------------------------------------------------------------------------
//
// - Content alignment options
// - Justification options
// - Text wrapping options
// - Overflow policy
// - Line height
//
// -----------------------------------------------------------------------------
//
// class inkText extends inkLeafWidget {
//   public func GetContentHAlign() -> inkEHorizontalAlign
//   public func SetContentHAlign(contentHAlign: inkEHorizontalAlign)
//   public func GetContentVAlign() -> inkEVerticalAlign
//   public func SetContentVAlign(contentVAlign: inkEVerticalAlign)
//   public func GetJustificationType() -> textJustificationType
//   public func SetJustificationType(justificationType: textJustificationType)
//   public func GetOverflowPolicy() -> textOverflowPolicy
//   public func SetOverflowPolicy(overflowPolicy: textOverflowPolicy)
//   public func SetWrapping(enabled: Bool, opt width: Float, opt policy: textWrappingPolicy)
//   public func GetLineHeight() -> Float
//   public func SetLineHeight(lineHeight: Float)
//   public func GetLockFontInGame() -> Bool
//   public func SetLockFontInGame(lockFont: Bool)
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

@addField(inkText)
native let lockFontInGame: Bool;

@addMethod(inkText)
public func GetContentHAlign() -> inkEHorizontalAlign {
    return this.contentHAlign;
}

@addMethod(inkText)
public func SetContentHAlign(contentHAlign: inkEHorizontalAlign) {
    this.contentHAlign = contentHAlign;
}

@addMethod(inkText)
public func GetContentVAlign() -> inkEVerticalAlign {
    return this.contentVAlign;
}

@addMethod(inkText)
public func SetContentVAlign(contentVAlign: inkEVerticalAlign) {
    this.contentVAlign = contentVAlign;
}

@addMethod(inkText)
public func GetJustificationType() -> textJustificationType {
    return this.justification;
}

@addMethod(inkText)
public func SetJustificationType(justificationType: textJustificationType) {
    this.justification = justificationType;
}

@addMethod(inkText)
public func GetOverflowPolicy() -> textOverflowPolicy {
    return this.textOverflowPolicy;
}

@addMethod(inkText)
public func SetOverflowPolicy(overflowPolicy: textOverflowPolicy) {
    this.textOverflowPolicy = overflowPolicy;
}

@addMethod(inkText)
public func SetWrapping(enabled: Bool, opt width: Float, opt policy: textWrappingPolicy) {
    this.wrappingInfo.autoWrappingEnabled = enabled;
    this.wrappingInfo.wrappingAtPosition = width;
    this.wrappingInfo.wrappingPolicy = policy;
}

@addMethod(inkText)
public func GetWrapping() -> textWrappingInfo {
    return this.wrappingInfo;
}

@addMethod(inkText)
public func GetLineHeight() -> Float {
    return this.lineHeightPercentage;
}

@addMethod(inkText)
public func SetLineHeight(lineHeight: Float) {
    this.lineHeightPercentage = lineHeight;
}

@addMethod(inkText)
public func GetLockFontInGame() -> Bool {
    return this.lockFontInGame;
}

@addMethod(inkText)
public func SetLockFontInGame(lockFont: Bool) {
    this.lockFontInGame = lockFont;
}
