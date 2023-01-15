// -----------------------------------------------------------------------------
// inkScrollController
// -----------------------------------------------------------------------------
//
// - Viewport are size
//
// -----------------------------------------------------------------------------
//
// class inkScrollController extends inkLeafWidget {
//   public func GetFitToContentDirection() -> inkFitToContentDirection
//   public func SetFitToContentDirection(value: inkFitToContentDirection) -> Void
// }
//

@addField(inkScrollController)
native let viewportSize: Vector2;

@addField(inkScrollController)
native let scrollDelta: Float;

@addField(inkScrollController)
private let lastScrollDelta: Float;

@addMethod(inkScrollController)
public func GetViewportSize() -> Vector2 {
    return this.viewportSize;
}

@addMethod(inkScrollController)
public func SetViewportSize(size: Vector2) -> Void {
    this.viewportSize = size;
}

@addMethod(inkScrollController)
public func SetViewportWidth(width: Float) -> Void {
    this.viewportSize = new Vector2(width, this.viewportSize.Y);
}

@addMethod(inkScrollController)
public func SetViewportHeight(height: Float) -> Void {
    this.viewportSize = new Vector2(this.viewportSize.X, height);
}

@addMethod(inkScrollController)
public func IsEnabled() -> Bool {
    return this.scrollDelta > 0.0;
}

@addMethod(inkScrollController)
public func SetEnabled(enabled: Bool) -> Void {
    if enabled {
        if this.lastScrollDelta > 0.0 {
            this.scrollDelta = this.lastScrollDelta;
        }
    } else {
        if this.scrollDelta > 0.0 {
            this.lastScrollDelta = this.scrollDelta;
        }
        this.scrollDelta = 0.0;
    }
}
