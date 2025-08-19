public native struct animSTwoBonesIKSolverData {
  public native let upperBone: animTransformIndex;
  public native let jointBone: animTransformIndex;
  public native let subLowerBone: animTransformIndex;
  public native let lowerBone: animTransformIndex;
  public native let ikBone: animTransformIndex;
  public native let limitToLengthPercentage: Float;
  public native let reverseBend: Bool;
  public native let allowToLock: Bool;
  public native let autoSetupDirs: Bool;
  public native let jointSideWeightUpper: Float;
  public native let jointSideWeightJoint: Float;
  public native let jointSideWeightLower: Float;
}
