@addMethod(EntityID)
public static native func FromHash(hash: Uint64) -> EntityID

@addMethod(EntityID)
public static native func ToHash(id: EntityID) -> Uint64
