public native struct animRigPart {
  public native let name: CName;
  public native let singleBones: array<animRigPartBone>;
  public native let treeBones: array<animRigPartBoneTree>;
  public native let bonesWithRotationInModelSpace: array<CName>;
  public native let mask: array<animTransformMask>;
  public native let maskRotMS: array<Int32>;
}
