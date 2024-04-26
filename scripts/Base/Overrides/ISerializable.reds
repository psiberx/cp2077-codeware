public abstract native class ISerializable {
    public final native func GetClassName() -> CName
    public final native func IsA(className: CName) -> Bool
    public final native func IsExactlyA(className: CName) -> Bool
    public final native func Clone() -> ref<ISerializable>
}
