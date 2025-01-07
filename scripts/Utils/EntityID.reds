public static func ToEntityID(value: Uint64) -> EntityID = EntityID.FromHash(value)
public static func ToEntityID(value: NodeRef) -> EntityID = EntityID.FromHash(NodeRefToHash(value))
