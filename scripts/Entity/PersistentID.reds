@addMethod(PersistentID)
public static native func ForEntity(id: EntityID) -> PersistentID

@addMethod(PersistentID)
public static native func ForComponent(id: EntityID, component: CName) -> PersistentID

@addMethod(PersistentID)
public static native func ToHash(id: script_ref<PersistentID>) -> Uint64
