public native struct animPoseCorrection {
  native let rbfCoefficient: Float;
  native let rbfPowValue: Float;
  native let compareBones: [animCompareBone; 4];
  native let boneCorrections: [animBoneCorrection; 4];
}
