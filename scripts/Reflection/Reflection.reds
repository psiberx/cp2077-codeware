public native struct Reflection {
    public static native func GetTypeOf(value: Variant) -> ref<ReflectionType>
    public static native func GetClassOf(object: Variant, opt actual: Bool) -> ref<ReflectionClass>
    public static native func GetType(name: CName) -> ref<ReflectionType>
    public static native func GetClass(name: CName) -> ref<ReflectionClass>
    public static native func GetEnum(name: CName) -> ref<ReflectionEnum>
    public static native func GetGlobalFunction(name: CName) -> ref<ReflectionStaticFunc>
    public static native func GetTypes() -> array<ref<ReflectionType>>
    public static native func GetClasses() -> array<ref<ReflectionClass>>
    public static native func GetDerivedClasses(base: CName) -> array<ref<ReflectionClass>>
    public static native func GetEnums() -> array<ref<ReflectionEnum>>
    public static native func GetGlobalFunctions() -> array<ref<ReflectionStaticFunc>>
}
