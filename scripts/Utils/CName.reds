public native func HashToName(value: Uint64) -> CName
public native func NameToHash(value: CName) -> Uint64

public func ToName(value: String) -> CName = StringToName(value)
public func ToName(value: Uint64) -> CName = HashToName(value)
