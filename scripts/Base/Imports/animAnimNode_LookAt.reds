public native class animAnimNode_LookAt extends animAnimNode_OnePoseInput {
  native let transform: animTransformIndex;
  native let forwardAxis: animAxis;
  native let useLimits: Bool;
  native let limitAxis: animAxis;
  native let limitAngle: Float;
  native let targetNode: animVectorLink;
  native let weightNode: animFloatLink;
}
