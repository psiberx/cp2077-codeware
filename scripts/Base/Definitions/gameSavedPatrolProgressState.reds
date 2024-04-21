public native class gameSavedPatrolProgressState extends ISerializable {
  native persistent let entrySplineParam: Float;
  native persistent let entrySectionIndex: Uint32;
  native persistent let controlPointIndex: Uint32;
  native persistent let splineEntryPosition: Vector3;
  native persistent let splineEntryTangent: Vector3;
  native persistent let isSplineReversed: Bool;
  native persistent let currentDestinationPosition: Vector3;
  native persistent let currentDestinationTangent: Vector3;
}
