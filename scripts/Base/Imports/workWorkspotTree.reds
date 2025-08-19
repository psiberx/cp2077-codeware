public native class workWorkspotTree extends ISerializable {
  public native let workspotRig: ResourceAsyncRef; // raRef<animRig>
  public native let globalProps: array<workWorkspotGlobalProp>;
  public native let propsPlaySyncAnim: Bool;
  public native let rootEntry: ref<workIEntry>;
  public native let idCounter: Uint32;
  public native let dontInjectWorkspotGraph: Bool;
  public native let animGraphSlotName: CName;
  public native let autoTransitionBlendTime: Float;
  public native let initialActions: array<ref<workIWorkspotItemAction>>;
  public native let initialCanUseExits: Bool;
  public native let blendOutTime: Float;
  public native let finalAnimsets: array<workWorkspotAnimsetEntry>;
  public native let tags: redTagList;
  public native let customTransitionAnims: array<workTransitionAnim>;
  public native let inertializationDurationEnter: Float;
  public native let inertializationDurationExitNatural: Float;
  public native let inertializationDurationExitForced: Float;
  public native let useTimeLimitForSequences: Bool;
  public native let frezeAtTheLastFrame_UseWithCaution: Bool;
  public native let sequencesTimeLimit: Float;
  public native let snapToTerrain: Bool;
  public native let unmountBodyCarry: Bool;
  public native let statusEffectID: TweakDBID;
  public native let whitelistVisualTags: redTagList;
  public native let blacklistVisualTags: redTagList;
}
