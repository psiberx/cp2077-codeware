public native class navLocomotionPath extends ISerializable {
  native let splineNodeRef: NodeRef;
  native let segments: array<navLocomotionPathSegmentInfo>;
  native let backwardSegments: array<navLocomotionPathSegmentInfo>;
  native let points: array<navLocomotionPathPointInfo>;
  native let userData: array<navLocomotionPathPointUserDataEntry>;
}
