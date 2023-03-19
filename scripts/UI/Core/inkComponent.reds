// -----------------------------------------------------------------------------
// inkComponent
// -----------------------------------------------------------------------------
//
// public abstract native class inkComponent extends inkLogicController {
//   protected cb func OnCreate()
//   protected cb func OnInitialize()
//   protected cb func OnUninitialize()
//   public func IsAttached() -> Bool
//   public func Reparent(newParent: wref<inkCompoundWidget>)
//   public func Reparent(newParent: wref<inkCompoundWidget>, index: Int32)
// }
//

public abstract native class inkComponent extends inkLogicController {
    public native func IsAttached() -> Bool

    public func Reparent(newParent: wref<inkCompoundWidget>) {
        this.Reparent(newParent, -1);
    }

    public func Reparent(newParent: wref<inkCompoundWidget>, index: Int32) {
        this.GetRootWidget().Reparent(newParent, index);
    }
}
