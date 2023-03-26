
enum ERTTIType
{
    Name = 0,
    Fundamental = 1,
    Class = 2,
    Array = 3,
    Simple = 4,
    Enum = 5,
    StaticArray = 6,
    NativeArray = 7,
    Pointer = 8,
    Handle = 9,
    WeakHandle = 10,
    ResourceReference = 11,
    ResourceAsyncReference = 12,
    BitField = 13,
    LegacySingleChannelCurve = 14,
    ScriptReference = 15,
    FixedArray = 16
}

public native struct Reflection {
    public static native func ResolveType(value: Variant) -> ref<ReflectionType>
    public static native func GetType(name: CName) -> ref<ReflectionType>
    public static native func GetClass(name: CName) -> ref<ReflectionClass>
    public static native func GetEnum(name: CName) -> ref<ReflectionEnum>
    public static native func GetGlobalFunction(name: CName) -> ref<ReflectionStaticFunc>
    public static native func GetTypes() -> array<ref<ReflectionType>>
    public static native func GetClasses() -> array<ref<ReflectionClass>>
    public static native func GetEnums() -> array<ref<ReflectionEnum>>
    public static native func GetGlobalFunctions() -> array<ref<ReflectionStaticFunc>>
}

public native class ReflectionType {
    public native func GetName() -> CName
    public native func GetMetaType() -> ERTTIType
    public native func GetInnerType() -> ref<ReflectionType>

    public func IsArray() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Array);
    }

    public func IsClass() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Class);
    }

    public func IsEnum() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Enum);
    }

    public func AsClass() -> ref<ReflectionClass> {
        return Reflection.GetClass(this.GetName());
    }

    public func AsEnum() -> ref<ReflectionEnum> {
        return Reflection.GetEnum(this.GetName());
    }
}

public native class ReflectionClass extends ReflectionType {
    public native func GetParent() -> ref<ReflectionClass>
    public native func GetProperty(name: CName) -> ref<ReflectionProp>
    public native func GetFunction(name: CName) -> ref<ReflectionMemberFunc>
    public native func GetStaticFunction(name: CName) -> ref<ReflectionStaticFunc>
    public native func GetProperties() -> array<ref<ReflectionProp>>
    public native func GetFunctions() -> array<ref<ReflectionMemberFunc>>
    public native func GetStaticFunctions() -> array<ref<ReflectionStaticFunc>>
    public native func IsNative() -> Bool
    public native func IsAbstract() -> Bool
}

public native class ReflectionProp {
    public native func GetName() -> CName
    public native func GetType() -> ref<ReflectionType>
    public native func IsNative() -> Bool
    // public native func Assign(owner: Variant, value: Variant)
}

public native class ReflectionFunc {
    public native func GetName() -> CName
    public native func GetFullName() -> CName
    public native func GetParameters() -> array<ref<ReflectionProp>>
    public native func GetReturnType() -> ref<ReflectionType>
    public native func IsNative() -> Bool
    public native func IsStatic() -> Bool
}

public native class ReflectionMemberFunc extends ReflectionFunc {
    // public native func Call(target: ref<IScriptable>, args: array<Variant>, out ret: Variant) -> Bool
}

public native class ReflectionStaticFunc extends ReflectionFunc {
    // public native func Call(args: array<Variant>, out ret: Variant) -> Bool
}

public native class ReflectionConst {
    public native func GetName() -> CName
    public native func GetValue() -> Int64
}

public native class ReflectionEnum extends ReflectionType {
    public native func GetConstants() -> array<ref<ReflectionConst>>
    public native func IsNative() -> Bool
}
