// Game 2.5 declares `native importonly class ISerializable` with no members.
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
