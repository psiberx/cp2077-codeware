public native struct scnChoiceNodeOption {
  native let screenplayOptionId: scnscreenplayItemId;
  native let caption: CName;
  native let blueline: Bool;
  native let isFixedAsRead: Bool;
  native let isSingleChoice: Bool;
  native let type: ChoiceTypeWrapper;
  native let timedParams: ref<scnChoiceNodeNsTimedParams>;
  native let questCondition: ref<questIBaseCondition>;
  native let triggerCondition: ref<questIBaseCondition>;
  native let bluelineCondition: ref<questIBaseCondition>;
  native let emphasisCondition: ref<questIBaseCondition>;
  native let iconCondition: ref<questIBaseCondition>;
  native let gameplayAction: TweakDBID;
  native let iconTagIds: array<TweakDBID>;
  native let exDataFlags: Uint32;
  native let mappinReferencePointId: scnReferencePointId;
  native let timedCondition: ref<scnTimedCondition>;
}
