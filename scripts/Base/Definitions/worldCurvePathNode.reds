public native class worldCurvePathNode extends worldSplineNode {
  native let userInput: animCurvePathBakerUserInput;
  native let defaultForwardVector: Vector4;
  native let globalInBlendTime: Float;
  native let globalOutBlendTime: Float;
  native let defaultPoseAnimationName: CName;
  native let defaultPoseSampleTime: Float;
  native let initialDiffYaw: Float;
  native let turnCharacterToMatchVelocity: Bool;
  native let rig: ResourceRef; // rRef<animRig>
  native let animSets: array<ResourceRef>;
  native let timeDeltaMultiplier: Float;
}
