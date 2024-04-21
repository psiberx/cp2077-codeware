public native struct animSTwoBonesIKSolverData {
  native let upperBone: animTransformIndex;
  native let jointBone: animTransformIndex;
  native let subLowerBone: animTransformIndex;
  native let lowerBone: animTransformIndex;
  native let ikBone: animTransformIndex;
  native let limitToLengthPercentage: Float;
  native let reverseBend: Bool;
  native let allowToLock: Bool;
  native let autoSetupDirs: Bool;
  native let jointSideWeightUpper: Float;
  native let jointSideWeightJoint: Float;
  native let jointSideWeightLower: Float;
}
