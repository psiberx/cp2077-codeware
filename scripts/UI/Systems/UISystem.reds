
@addMethod(UISystem)
public native func GetVirtualWindows() -> array<ref<inkVirtualWindow>>;

@addMethod(UISystem)
public native func GetVirtualWindow(layer: CName) -> ref<inkVirtualWindow>;
