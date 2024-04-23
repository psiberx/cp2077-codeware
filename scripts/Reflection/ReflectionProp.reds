public native class ReflectionProp {
    public native func GetName() -> CName
    public native func GetType() -> ref<ReflectionType>
    public native func IsNative() -> Bool
    public native func GetValue(owner: Variant) -> Variant
    public native func SetValue(owner: Variant, value: Variant)
}
