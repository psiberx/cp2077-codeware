@addMethod(inkScrollController)
public func GetScrollPosition() -> Float {
    return this.position;
}

@addMethod(inkScrollController)
public func GetContentSize() -> Vector2 {
    return this.contentSize;
}

@addMethod(inkScrollController)
public func GetViewportSize() -> Vector2 {
    return this.viewportSize;
}

@addMethod(inkScrollController)
public func SetViewportSize(size: Vector2) {
    this.viewportSize = size;
}

@addMethod(inkScrollController)
public func SetViewportWidth(width: Float) {
    this.viewportSize = Vector2(width, this.viewportSize.Y);
}

@addMethod(inkScrollController)
public func SetViewportHeight(height: Float) {
    this.viewportSize = Vector2(this.viewportSize.X, height);
}

@addMethod(inkScrollController)
public func IsEnabled() -> Bool {
    return this.scrollDelta > 0.0;
}

@addMethod(inkScrollController)
public func SetEnabled(enabled: Bool) {
    if enabled {
        if Equals(this.direction, inkEScrollDirection.Horizontal) {
            this.scrollDelta = this.contentSize.X - this.viewportSize.X;
        } else {
            this.scrollDelta = this.contentSize.Y - this.viewportSize.Y;
        }
    } else {
        this.scrollDelta = 0.0;
    }
}
