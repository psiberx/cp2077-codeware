public native class animRig extends CResource {
  native let boneNames: array<CName>;
  native let trackNames: array<CName>;
  native let rigExtraTracks: array<animFloatTrackInfo>;
  native let levelOfDetailStartIndices: array<Int16>;
  native let distanceCategoryToLodMap: array<Int16>;
  native let turnOffLOD: Int32;
  native let turningOffUpdateAndSample: Bool;
  native let referenceTracks: array<Float>;
  native let referencePoseMS: array<QsTransform>;
  native let aPoseLS: array<QsTransform>;
  native let aPoseMS: array<QsTransform>;
  native let tags: redTagList;
  native let parts: array<animRigPart>;
  native let retargets: array<animRigRetarget>;
  native let ikSetups: array<ref<animIRigIkSetup>>;
  native let ragdollDesc: array<physicsRagdollBodyInfo>;
  native let ragdollNames: array<physicsRagdollBodyNames>;
}
