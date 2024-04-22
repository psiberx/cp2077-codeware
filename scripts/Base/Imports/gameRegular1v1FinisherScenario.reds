public native class gameRegular1v1FinisherScenario extends gameIFinisherScenario {
  native let attackerWorkspot: ResourceAsyncRef; // raRef<workWorkspotResource>
  native let targetWorkspot: ResourceAsyncRef; // raRef<workWorkspotResource>
  native let syncData: array<gameFinisherSyncData>;
  native let targetPlaybackDelay: Float;
  native let targetBlendTime: Float;
  native let attackerPlaybackDelay: Float;
  native let attackerBlendTime: Float;
  native let pivotSettings: gameRegular1v1FinisherScenarioPivotSetting;
  native let attackerIsMaster: Bool;
  native let targetSlotNameToAttachAttackerWeaponLeft: CName;
}
