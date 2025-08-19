public native struct gameSmartObjectPropertyDictionaryPropertyEntry {
  public native let id: Uint16;
  public native let usage: Uint32;
  public native let animationName: CName;
  public native let sourceAnimset: Uint64;
  public native let type: gameSmartObjectPointType;
  public native let movementType: moveMovementType;
  public native let movementOrientation: moveMovementOrientationType;
  public native let isOnNavmesh: Bool;
  public native let isReachable: Bool;
  public native let overObstacle: Bool;
}
