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
