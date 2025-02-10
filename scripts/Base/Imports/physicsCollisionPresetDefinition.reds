@neverRef() public native class physicsCollisionPresetDefinition extends ISerializable {
  native let Name: CName;
  native let Description: String;
  native let ForceEnableCollisionCallbacks: Bool;
  native let CollisionType: array<CName>;
  native let CollisionMask: array<CName>;
  native let QueryDetect: array<CName>;
}

