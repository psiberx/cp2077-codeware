public native class gameRegular1v1FinisherScenario extends gameIFinisherScenario {
  public native let attackerWorkspot: ResourceAsyncRef; // raRef<workWorkspotResource>
  public native let targetWorkspot: ResourceAsyncRef; // raRef<workWorkspotResource>
  public native let syncData: array<gameFinisherSyncData>;
  public native let targetPlaybackDelay: Float;
  public native let targetBlendTime: Float;
  public native let attackerPlaybackDelay: Float;
  public native let attackerBlendTime: Float;
  public native let pivotSettings: gameRegular1v1FinisherScenarioPivotSetting;
  public native let attackerIsMaster: Bool;
  public native let targetSlotNameToAttachAttackerWeaponLeft: CName;
}
