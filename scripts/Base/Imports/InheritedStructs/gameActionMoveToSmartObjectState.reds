public native struct gameActionMoveToSmartObjectState {
  native let targetPos: Vector3;
  native let toleranceRadius: Float;
  native let rotateEntity: Bool;
  native let moveStyle: Uint32;

  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;

  native let targetHash: Uint64;
  native let usePathfinding: Bool;
  native let useStart: Bool;
  native let useStop: Bool;
  native let entryType: gameSmartObjectInstanceEntryType;
  native let movementType: moveMovementType;
  native let strafingTarget: wref<GameObject>;
  native let entryDirection: Vector3;
  native let entryPointPos: Vector3;
  native let entryPointDir: Vector4;
  native let animationName: CName;
  native let isInSmartObject: Bool;
}
