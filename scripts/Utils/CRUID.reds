public static native func HashToCRUID(value: Uint64) -> CRUID
public static native func CRUIDToHash(value: CRUID) -> Uint64

public static func CreateCRUID(value: Uint64) -> CRUID = HashToCRUID(value)
public static func ToCRUID(value: Uint64) -> CRUID = HashToCRUID(value)

public static func Cast(value: CRUID) -> Uint64 = CRUIDToHash(value)
public static func Cast(value: Uint64) -> CRUID = HashToCRUID(value)
