
public native struct ResourceRef {
    public static native func LoadPath(self: script_ref<ResourceRef>, path: ResRef)
    public static native func GetPath(self: script_ref<ResourceRef>) -> ResRef
    public static native func GetHash(self: script_ref<ResourceRef>) -> Uint64
    //public static native func GetToken(self: script_ref<ResourceRef>) -> ref<ResourceToken>
    public static native func IsEmpty(self: script_ref<ResourceRef>) -> Bool
    public static native func IsLoaded(self: script_ref<ResourceRef>) -> Bool
    public static native func IsFailed(self: script_ref<ResourceRef>) -> Bool
}

public native struct ResourceAsyncRef {
    public static native func SetPath(self: script_ref<ResourceAsyncRef>, path: ResRef)
    public static native func GetPath(self: script_ref<ResourceAsyncRef>) -> ResRef
    public static native func GetHash(self: script_ref<ResourceAsyncRef>) -> Uint64
    public static native func IsEmpty(self: script_ref<ResourceAsyncRef>) -> Bool
}

public static func OperatorAssignMultiply(out res: ResourceRef, path: ResRef) {
    ResourceRef.LoadPath(res, path);
}

public static func OperatorAssignMultiply(out res: ResourceAsyncRef, path: ResRef) {
    ResourceAsyncRef.SetPath(res, path);
}

@addMethod(ResRef)
public static native func GetHash(self: ResRef) -> Uint64

public static func OperatorEqual(lhs: ResRef, rhs: ResRef) -> Bool {
    return Equals(lhs, rhs);
}

public static func OperatorNotEqual(lhs: ResRef, rhs: ResRef) -> Bool {
    return NotEquals(lhs, rhs);
}
