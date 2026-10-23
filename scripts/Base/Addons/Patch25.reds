// Members the game declarations lack since patch 2.5, provided natively by Codeware.

@addMethod(ISerializable)
public final native func GetClassName() -> CName

@addMethod(ISerializable)
public final native func IsA(className: CName) -> Bool

@addMethod(ISerializable)
public final native func IsExactlyA(className: CName) -> Bool

@addMethod(ISerializable)
public final native func Clone() -> ref<ISerializable>

@addMethod(ISerializable)
public final native func ProcessPostLoad(opt disablePreInitialization: Bool)

@addMethod(ISerializable)
public final func RefreshResource(opt disablePreInitialization: Bool) {
    this.ProcessPostLoad(disablePreInitialization);
}

@addField(CResource)
native let path: ResRef;

@addField(inkContainerNavigationController)
public native let overrideEntries: array<inkNavigationOverrideEntry>;

@addField(inkContainerNavigationController)
public native let useGlobalInput: Bool;
