public native class animAnimNode_LookAtController extends animAnimNode_OnePoseInput {
  native let E3_HACK_offset: animVectorLink;
  native let orderedBodyParts: array<LookAtPartInfo>;
  native let stateMachinesSettings: array<LookAtStateMachineSettings>;
  native let bodyPartsDependencies: array<LookAtPartsDependency>;
  native let substepTime: Float;
  native let isFacial: Bool;
}
