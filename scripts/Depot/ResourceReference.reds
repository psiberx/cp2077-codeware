public native struct ResourceRef {
    public static native func LoadPath(self: script_ref<ResourceRef>, path: ResRef)
    public static native func GetPath(self: script_ref<ResourceRef>) -> ResRef
    public static native func GetHash(self: script_ref<ResourceRef>) -> Uint64
    public static native func GetToken(self: script_ref<ResourceRef>) -> ref<ResourceToken>
    public static native func GetResource(self: script_ref<ResourceRef>) -> ref<CResource>
    public static native func IsEmpty(self: script_ref<ResourceRef>) -> Bool
    public static native func IsLoaded(self: script_ref<ResourceRef>) -> Bool
    public static native func IsFailed(self: script_ref<ResourceRef>) -> Bool
    //public static native func ToString(self: script_ref<ResourceRef>) -> String
    public static native func ToVariant(self: script_ref<ResourceRef>, type: CName) -> Variant
    public static native func FromVariant(variant: Variant) -> ResourceRef

    public static func FromPath(path: ResRef) -> ResourceRef {
        let reference: ResourceRef;
        ResourceRef.LoadPath(reference, path);
        return reference;
    }
}

public native struct ResourceAsyncRef {
    public static native func SetPath(self: script_ref<ResourceAsyncRef>, path: ResRef)
    public static native func GetPath(self: script_ref<ResourceAsyncRef>) -> ResRef
    public static native func GetHash(self: script_ref<ResourceAsyncRef>) -> Uint64
    public static native func IsEmpty(self: script_ref<ResourceAsyncRef>) -> Bool
    //public static native func ToString(self: script_ref<ResourceAsyncRef>) -> String
}

public func OperatorAssignMultiply(out res: ResourceRef, path: ResRef) {
    ResourceRef.LoadPath(res, path);
}

public func OperatorAssignMultiply(out res: ResourceAsyncRef, path: ResRef) {
    ResourceAsyncRef.SetPath(res, path);
}

@addMethod(ResRef)
public static native func GetHash(self: ResRef) -> Uint64

@addMethod(ResRef)
public static native func ToString(self: ResRef) -> String

public func OperatorEqual(lhs: ResourceAsyncRef, rhs: ResRef) -> Bool {
    return Equals(ResourceAsyncRef.GetPath(lhs), rhs);
}

public func OperatorNotEqual(lhs: ResourceAsyncRef, rhs: ResRef) -> Bool {
    return NotEquals(ResourceAsyncRef.GetPath(lhs), rhs);
}

public func OperatorEqual(lhs: ResRef, rhs: ResRef) -> Bool {
    return Equals(lhs, rhs);
}

public func OperatorNotEqual(lhs: ResRef, rhs: ResRef) -> Bool {
    return NotEquals(lhs, rhs);
}
