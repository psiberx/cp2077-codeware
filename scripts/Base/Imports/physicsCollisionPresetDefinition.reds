@neverRef()
public native class physicsCollisionPresetDefinition extends ISerializable {
  public native let Name: CName;
  public native let Description: String;
  public native let ForceEnableCollisionCallbacks: Bool;
  public native let CollisionType: array<CName>;
  public native let CollisionMask: array<CName>;
  public native let QueryDetect: array<CName>;
}
