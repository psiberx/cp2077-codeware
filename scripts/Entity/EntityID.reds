@addMethod(EntityID)
public static native func FromHash(hash: Uint64) -> EntityID

@addMethod(EntityID)
public static native func ToHash(id: script_ref<EntityID>) -> Uint64
