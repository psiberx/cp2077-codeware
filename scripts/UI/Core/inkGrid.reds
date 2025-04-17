public native class inkGrid extends inkCompoundWidget {
    native let orientation: inkEOrientation;
    native let childPadding: inkMargin;
    native let childSizeStep: Vector2;

    public func GetOrientation() -> inkEOrientation {
        return this.orientation;
    }

    public func SetOrientation(value: inkEOrientation) {
        this.orientation = value;
    }

    public func GetChildPadding() -> inkMargin {
        return this.childPadding;
    }

    public func SetChildPadding(value: inkMargin) {
        this.childPadding = value;
    }

    public func GetChildSizeStep() -> Vector2 {
        return this.childSizeStep;
    }

    public func SetChildSizeStep(value: Vector2) {
        this.childSizeStep = value;
    }
}
