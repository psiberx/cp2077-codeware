public native class physicsSystemJoint extends physicsISystemObject {
  public native let localToWorld: Matrix;
  public native let pinA: ref<physicsPhysicalJointPin>;
  public native let pinB: ref<physicsPhysicalJointPin>;
  public native let linearLimit: physicsPhysicsJointLinearLimit;
  public native let twistLimit: physicsPhysicsJointAngularLimitPair;
  public native let swingLimit: physicsPhysicsJointLimitConePair;
  public native let driveY: physicsPhysicsJointDrive;
  public native let driveX: physicsPhysicsJointDrive;
  public native let driveZ: physicsPhysicsJointDrive;
  public native let driveTwist: physicsPhysicsJointDrive;
  public native let driveSwing: physicsPhysicsJointDrive;
  public native let driveSLERP: physicsPhysicsJointDrive;
  public native let driveVelocity: physicsPhysicsJointDriveVelocity;
  public native let drivePosition: Matrix;
  public native let projectionEnabled: Bool;
  public native let linearTolerance: Float;
  public native let angularTolerance: Float;
  public native let isBreakable: Bool;
  public native let breakingForce: Float;
  public native let breakingTorque: Float;
}
