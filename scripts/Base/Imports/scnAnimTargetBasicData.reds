public native struct scnAnimTargetBasicData {
  public native let performerId: scnPerformerId;
  public native let isStart: Bool;
  public native let targetPerformerId: scnPerformerId;
  public native let targetSlot: CName;
  public native let targetOffsetEntitySpace: Vector4;
  public native let staticTarget: Vector4;
  public native let targetActorId: scnActorId;
  public native let targetPropId: scnPropId;
  public native let targetType: scnLookAtTargetType;
}
