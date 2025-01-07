public static native func HashToName(value: Uint64) -> CName
public static native func NameToHash(value: CName) -> Uint64

public static func ToName(value: String) -> CName = StringToName(value)
public static func ToName(value: Uint64) -> CName = HashToName(value)
