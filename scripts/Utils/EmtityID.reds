public static func ToEntityID(value: Uint64) -> EntityID = EntityID.FromHash(value)

public static func Cast(value: Uint64) -> EntityID = EntityID.FromHash(value)
public static func Cast(value: EntityID) -> Uint64 = EntityID.ToHash(value)
