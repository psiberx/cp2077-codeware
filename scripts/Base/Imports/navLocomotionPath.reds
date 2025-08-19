public native class navLocomotionPath extends ISerializable {
  public native let splineNodeRef: NodeRef;
  public native let segments: array<navLocomotionPathSegmentInfo>;
  public native let backwardSegments: array<navLocomotionPathSegmentInfo>;
  public native let points: array<navLocomotionPathPointInfo>;
  public native let userData: array<navLocomotionPathPointUserDataEntry>;
}
