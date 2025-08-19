public native class gameSavedPatrolProgressState extends ISerializable {
  public native persistent let entrySplineParam: Float;
  public native persistent let entrySectionIndex: Uint32;
  public native persistent let controlPointIndex: Uint32;
  public native persistent let splineEntryPosition: Vector3;
  public native persistent let splineEntryTangent: Vector3;
  public native persistent let isSplineReversed: Bool;
  public native persistent let currentDestinationPosition: Vector3;
  public native persistent let currentDestinationTangent: Vector3;
}
