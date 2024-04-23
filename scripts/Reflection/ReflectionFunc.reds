public native class ReflectionFunc {
    public native func GetName() -> CName
    public native func GetFullName() -> CName
    public native func GetParameters() -> array<ref<ReflectionProp>>
    public native func GetReturnType() -> ref<ReflectionType>
    public native func IsNative() -> Bool
    public native func IsStatic() -> Bool
}

public native class ReflectionMemberFunc extends ReflectionFunc {
    public native func Call(self: ref<IScriptable>, opt args: array<Variant>, opt status: script_ref<Bool>) -> Variant
}

public native class ReflectionStaticFunc extends ReflectionFunc {
    public native func Call(opt args: array<Variant>, opt status: script_ref<Bool>) -> Variant
}
