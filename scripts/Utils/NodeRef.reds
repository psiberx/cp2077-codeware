public static native func CreateNodeRef(value: script_ref<String>) -> NodeRef
public static native func HashToNodeRef(value: Uint64) -> NodeRef
public static native func NodeRefToHash(value: NodeRef) -> Uint64

public static func ToNodeRef(value: String) -> NodeRef = CreateNodeRef(value)
public static func ToNodeRef(value: Uint64) -> NodeRef = HashToNodeRef(value)

public static func Cast(value: NodeRef) -> Uint64 = NodeRefToHash(value)
public static func Cast(value: NodeRef) -> EntityID = EntityID.FromHash(NodeRefToHash(value))
public static func Cast(value: EntityID) -> NodeRef = HashToNodeRef(EntityID.ToHash(value))
public static func Cast(value: Uint64) -> NodeRef = HashToNodeRef(value)
public static func Cast(value: String) -> NodeRef = CreateNodeRef(value)
