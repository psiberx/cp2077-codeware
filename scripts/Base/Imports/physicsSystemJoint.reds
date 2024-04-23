public native class physicsSystemJoint extends physicsISystemObject {
  native let localToWorld: Matrix;
  native let pinA: ref<physicsPhysicalJointPin>;
  native let pinB: ref<physicsPhysicalJointPin>;
  native let driveY: physicsPhysicsJointDrive;
  native let driveX: physicsPhysicsJointDrive;
  native let driveZ: physicsPhysicsJointDrive;
  native let driveTwist: physicsPhysicsJointDrive;
  native let driveSwing: physicsPhysicsJointDrive;
  native let driveSLERP: physicsPhysicsJointDrive;
  native let driveVelocity: physicsPhysicsJointDriveVelocity;
  native let drivePosition: Matrix;
  native let projectionEnabled: Bool;
  native let linearTolerance: Float;
  native let angularTolerance: Float;
  native let isBreakable: Bool;
  native let breakingForce: Float;
  native let breakingTorque: Float;
}
