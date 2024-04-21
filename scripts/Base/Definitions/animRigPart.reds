public native struct animRigPart {
  native let name: CName;
  native let singleBones: array<animRigPartBone>;
  native let treeBones: array<animRigPartBoneTree>;
  native let bonesWithRotationInModelSpace: array<CName>;
  native let mask: array<animTransformMask>;
  native let maskRotMS: array<Int32>;
}
