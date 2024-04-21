public native class animAnimNode_BlendMultiple extends animAnimNode_Base {
  native let inputValues: array<Float>;
  native let sortedInputValues: array<Float>;
  native let minWeight: Float;
  native let maxWeight: Float;
  native let radialBlending: Bool;
  native let timeWarpingEnabled: Bool;
  native let weightNode: animFloatLink;
  native let inputNodes: array<animPoseLink>;
}
