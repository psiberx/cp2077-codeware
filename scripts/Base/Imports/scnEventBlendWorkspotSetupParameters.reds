public native class scnEventBlendWorkspotSetupParameters extends ISerializable {
  public native let workspotId: scnSceneWorkspotInstanceId;
  public native let sequenceEntryId: WorkEntryId;
  public native let idleOnlyMode: Bool;
  public native let workExcludedGestures: array<WorkEntryId>;
  public native let itemOverride: workWorkspotItemOverride;
}
