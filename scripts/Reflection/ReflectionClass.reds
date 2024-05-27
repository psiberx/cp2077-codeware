public native class ReflectionClass extends ReflectionType {
    public native func GetAlias() -> CName
    public native func GetParent() -> ref<ReflectionClass>
    public native func GetProperty(name: CName) -> ref<ReflectionProp>
    public native func GetFunction(name: CName) -> ref<ReflectionMemberFunc>
    public native func GetStaticFunction(name: CName) -> ref<ReflectionStaticFunc>
    public native func GetProperties() -> array<ref<ReflectionProp>>
    public native func GetFunctions() -> array<ref<ReflectionMemberFunc>>
    public native func GetStaticFunctions() -> array<ref<ReflectionStaticFunc>>
    public native func IsNative() -> Bool
    public native func IsAbstract() -> Bool
    public native func IsA(base: CName) -> Bool
    public native func MakeHandle() -> ref<ISerializable>
}
