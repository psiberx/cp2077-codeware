@addField(IComponent)
public native let appearanceName: CName;

@addField(IComponent)
public native let appearancePath: ResRef;

@addMethod(IComponent)
public native func ChangeResource(path: ResRef, opt wait: Bool) -> Bool

@addMethod(IComponent)
public native func ChangeAppearance(name: CName, opt wait: Bool) -> Bool

@addMethod(IComponent)
public native func LoadAppearance(opt wait: Bool) -> Bool

@addMethod(IComponent)
public native func RefreshAppearance() -> Bool

@addMethod(IComponent)
public native func ResetMaterialCache()
