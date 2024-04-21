public native struct gameSmartObjectPropertyDictionaryPropertyEntry {
  native let id: Uint16;
  native let usage: Uint32;
  native let animationName: CName;
  native let sourceAnimset: Uint64;
  native let type: gameSmartObjectPointType;
  native let movementType: moveMovementType;
  native let movementOrientation: moveMovementOrientationType;
  native let isOnNavmesh: Bool;
  native let isReachable: Bool;
  native let overObstacle: Bool;
}
