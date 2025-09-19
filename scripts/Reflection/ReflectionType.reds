public native class ReflectionType {
    public native func GetName() -> CName
    public native func GetMetaType() -> ERTTIType
    public native func GetInnerType() -> ref<ReflectionType>
    public native func MakeInstance() -> Variant

    public func IsArray() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Array);
    }

    public func IsClass() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Class);
    }

    public func IsEnum() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.Enum);
    }

    public func IsBitfield() -> Bool {
        return Equals(this.GetMetaType(), ERTTIType.BitField);
    }

    public func AsClass() -> ref<ReflectionClass> {
        let typed = this as ReflectionClass;
        return IsDefined(typed) ? typed : Reflection.GetClass(this.GetName());
    }

    public func AsEnum() -> ref<ReflectionEnum> {
        let typed = this as ReflectionEnum;
        return IsDefined(typed) ? typed : Reflection.GetEnum(this.GetName());
    }

    public func AsBitfield() -> ref<ReflectionBitfield> {
        let typed = this as ReflectionBitfield;
        return IsDefined(typed) ? typed : Reflection.GetBitfield(this.GetName());
    }
}
