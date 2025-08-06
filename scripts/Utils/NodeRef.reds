public native func CreateNodeRef(value: script_ref<String>) -> NodeRef
public native func HashToNodeRef(value: Uint64) -> NodeRef
public native func NodeRefToHash(value: NodeRef) -> Uint64

public func ToNodeRef(value: String) -> NodeRef = CreateNodeRef(value)
public func ToNodeRef(value: Uint64) -> NodeRef = HashToNodeRef(value)
public func ToNodeRef(value: EntityID) -> NodeRef = HashToNodeRef(EntityID.ToHash(value))
