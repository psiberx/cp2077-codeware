public native class worldCurvePathNode extends worldSplineNode {
  public native let userInput: animCurvePathBakerUserInput;
  public native let defaultForwardVector: Vector4;
  public native let globalInBlendTime: Float;
  public native let globalOutBlendTime: Float;
  public native let defaultPoseAnimationName: CName;
  public native let defaultPoseSampleTime: Float;
  public native let initialDiffYaw: Float;
  public native let turnCharacterToMatchVelocity: Bool;
  public native let rig: ResourceRef; // rRef<animRig>
  public native let animSets: array<ResourceRef>;
  public native let timeDeltaMultiplier: Float;
}
