public native struct scnAnimTargetBasicData {
  native let performerId: scnPerformerId;
  native let isStart: Bool;
  native let targetPerformerId: scnPerformerId;
  native let targetSlot: CName;
  native let targetOffsetEntitySpace: Vector4;
  native let staticTarget: Vector4;
  native let targetActorId: scnActorId;
  native let targetPropId: scnPropId;
  native let targetType: scnLookAtTargetType;
}
