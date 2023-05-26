@addField(inkScrollController)
native let ScrollArea: inkScrollAreaRef;

@addField(inkScrollController)
native let VerticalScrollBarRef: inkWidgetRef;

@addField(inkScrollController)
native let navigableCompoundWidget: inkWidgetRef;

@addField(inkScrollController)
native let CompoundWidgetRef: inkCompoundRef;

@addField(inkScrollController)
native let autoHideVertical: Bool;

@addField(inkScrollController)
native let scrollSpeedGamepad: Float;

@addField(inkScrollController)
native let scrollSpeedMouse: Float;

@addField(inkScrollController)
native let direction: inkEScrollDirection;

@addField(inkScrollController)
native let useGlobalInput: Bool;

@addField(inkScrollController)
native let desiredSetupPosition: Float;

@addField(inkScrollController)
native let contentSmallerThanViewport: Bool;

@addField(inkScrollController)
native let position: Float;

@addField(inkScrollController)
native let contentSize: Vector2;

@addField(inkScrollController)
native let viewportSize: Vector2;

@addField(inkScrollController)
native let scrollDelta: Float;

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
    this.viewportSize = new Vector2(width, this.viewportSize.Y);
}

@addMethod(inkScrollController)
public func SetViewportHeight(height: Float) {
    this.viewportSize = new Vector2(this.viewportSize.X, height);
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
