public native class workWorkspotTree extends ISerializable {
  native let workspotRig: ResourceAsyncRef; // raRef<animRig>
  native let globalProps: array<workWorkspotGlobalProp>;
  native let propsPlaySyncAnim: Bool;
  native let idCounter: Uint32;
  native let dontInjectWorkspotGraph: Bool;
  native let animGraphSlotName: CName;
  native let autoTransitionBlendTime: Float;
  native let initialCanUseExits: Bool;
  native let blendOutTime: Float;
  native let finalAnimsets: array<workWorkspotAnimsetEntry>;
  native let tags: redTagList;
  native let customTransitionAnims: array<workTransitionAnim>;
  native let inertializationDurationEnter: Float;
  native let inertializationDurationExitNatural: Float;
  native let inertializationDurationExitForced: Float;
  native let useTimeLimitForSequences: Bool;
  native let frezeAtTheLastFrame_UseWithCaution: Bool;
  native let sequencesTimeLimit: Float;
  native let snapToTerrain: Bool;
  native let unmountBodyCarry: Bool;
  native let statusEffectID: TweakDBID;
  native let whitelistVisualTags: redTagList;
  native let blacklistVisualTags: redTagList;
}
