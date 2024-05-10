public native struct gameNpcPuppetReplicatedState {
  native let initialOrientation: EulerAngles;
  native let initialLocation: Vector3;
  native let initialAppearance: CName;
  native let actionsBuffer: gameActionsReplicationBuffer;
  native let health: Float;
  native let armor: Float;
  native let hasCPOMissionData: Bool;
  native let CPOMissionVotedHistory: array<CName>;
  native let animEventsState: gameReplicatedAnimControllerEventsState;
  native let entityEventsState: gameReplicatedEntityEventsState;
  native let recordID: TweakDBID;
  native let persistentID: Uint64;
  native let weaponStates: gameWeaponsReplicatedState;
}
