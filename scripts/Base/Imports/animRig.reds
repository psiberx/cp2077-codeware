public native class animRig extends CResource {
  public native let boneNames: array<CName>;
  public native let trackNames: array<CName>;
  public native let rigExtraTracks: array<animFloatTrackInfo>;
  public native let levelOfDetailStartIndices: array<Int16>;
  public native let distanceCategoryToLodMap: array<Int16>;
  public native let turnOffLOD: Int32;
  public native let turningOffUpdateAndSample: Bool;
  public native let referenceTracks: array<Float>;
  public native let referencePoseMS: array<QsTransform>;
  public native let aPoseLS: array<QsTransform>;
  public native let aPoseMS: array<QsTransform>;
  public native let tags: redTagList;
  public native let parts: array<animRigPart>;
  public native let retargets: array<animRigRetarget>;
  public native let ikSetups: array<ref<animIRigIkSetup>>;
  public native let ragdollDesc: array<physicsRagdollBodyInfo>;
  public native let ragdollNames: array<physicsRagdollBodyNames>;
}
