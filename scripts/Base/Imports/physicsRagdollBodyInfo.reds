public native struct physicsRagdollBodyInfo {
  native let ParentAnimIndex: Int32;
  native let ChildAnimIndex: Int32;
  native let ParentBodyIndex: Int32;
  native let ShapeType: physicsRagdollShapeType;
  native let ShapeRadius: Float;
  native let HalfHeight: Float;
  native let ShapeLocalTranslation: Vector3;
  native let ShapeLocalRotation: Quaternion;
  native let IsRootDisplacementPart: Bool;
  native let SwingAnglesY: [Float; 2];
  native let SwingAnglesZ: [Float; 2];
  native let TwistAngles: [Float; 2];
  native let IsStiff: Bool;
  native let ExcludeFromEarlyCollision: Bool;
  native let FilterDataOverride: CName;
}
