@addMethod(inkScrollArea)
public func GetConstrainContentPosition() -> Bool {
    return this.constrainContentPosition;
}

@addMethod(inkScrollArea)
public func SetConstrainContentPosition(enabled: Bool) {
    this.constrainContentPosition = enabled;
}

@addMethod(inkScrollArea)
public func GetFitToContentDirection() -> inkFitToContentDirection {
    return this.fitToContentDirection;
}

@addMethod(inkScrollArea)
public func SetFitToContentDirection(value: inkFitToContentDirection) {
    this.fitToContentDirection = value;
}
