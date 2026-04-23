public native class worldCollisionNodeInstance extends worldINodeInstance {
  public native func GetPrimaryPhysicsProxyID() -> Uint32
  public native func GetOverflowPhysicsProxyID() -> Uint32
  public native func HasOverflowPhysicsProxy() -> Bool
  public native func GetCollisionActorCount() -> Int32
  public native func GetCollisionSplitIndex() -> Int32
  public native func ResolveActorIndex(hitProxyID: Uint32, localActorIndex: Uint32) -> Int32
}
