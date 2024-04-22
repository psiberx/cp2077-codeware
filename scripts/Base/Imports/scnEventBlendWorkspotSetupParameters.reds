public native class scnEventBlendWorkspotSetupParameters extends ISerializable {
  native let workspotId: scnSceneWorkspotInstanceId;
  native let sequenceEntryId: WorkEntryId;
  native let idleOnlyMode: Bool;
  native let workExcludedGestures: array<WorkEntryId>;
  native let itemOverride: workWorkspotItemOverride;
}
