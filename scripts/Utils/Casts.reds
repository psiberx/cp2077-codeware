public static func Cast(value: CName) -> Uint64 = NameToHash(value)
public static func Cast(value: Uint64) -> CName = HashToName(value)

public static func Cast(value: CRUID) -> Uint64 = CRUIDToHash(value)
public static func Cast(value: Uint64) -> CRUID = HashToCRUID(value)

public static func Cast(value: EntityID) -> Uint64 = EntityID.ToHash(value)
public static func Cast(value: Uint64) -> EntityID = EntityID.FromHash(value)

public static func Cast(value: NodeRef) -> Uint64 = NodeRefToHash(value)
public static func Cast(value: Uint64) -> NodeRef = HashToNodeRef(value)

public static func Cast(value: NodeRef) -> EntityID = EntityID.FromHash(NodeRefToHash(value))
public static func Cast(value: EntityID) -> NodeRef = HashToNodeRef(EntityID.ToHash(value))

public static func Cast(value: String) -> NodeRef = CreateNodeRef(value)

public static func Cast(value: LocalizationString) -> String = ExtractLocalizationString(value)
public static func Cast(value: String) -> LocalizationString = CreateLocalizationString(value)
