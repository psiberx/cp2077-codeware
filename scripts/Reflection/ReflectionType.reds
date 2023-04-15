
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
        return this as ReflectionClass;
    }

    public func AsEnum() -> ref<ReflectionEnum> {
        return this as ReflectionEnum;
    }
}
