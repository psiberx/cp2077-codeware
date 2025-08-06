public native func HashToCRUID(value: Uint64) -> CRUID
public native func CRUIDToHash(value: CRUID) -> Uint64

public func CreateCRUID(value: Uint64) -> CRUID = HashToCRUID(value)
public func ToCRUID(value: Uint64) -> CRUID = HashToCRUID(value)
