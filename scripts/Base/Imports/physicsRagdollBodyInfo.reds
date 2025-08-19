public native struct physicsRagdollBodyInfo {
  public native let ParentAnimIndex: Int32;
  public native let ChildAnimIndex: Int32;
  public native let ParentBodyIndex: Int32;
  public native let ShapeType: physicsRagdollShapeType;
  public native let ShapeRadius: Float;
  public native let HalfHeight: Float;
  public native let ShapeLocalTranslation: Vector3;
  public native let ShapeLocalRotation: Quaternion;
  public native let IsRootDisplacementPart: Bool;
  public native let SwingAnglesY: [Float; 2];
  public native let SwingAnglesZ: [Float; 2];
  public native let TwistAngles: [Float; 2];
  public native let IsStiff: Bool;
  public native let ExcludeFromEarlyCollision: Bool;
  public native let FilterDataOverride: CName;
}
