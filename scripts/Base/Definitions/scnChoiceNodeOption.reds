public native struct scnChoiceNodeOption {
  native let screenplayOptionId: scnscreenplayItemId;
  native let caption: CName;
  native let blueline: Bool;
  native let isFixedAsRead: Bool;
  native let isSingleChoice: Bool;
  native let type: ChoiceTypeWrapper;
  native let gameplayAction: TweakDBID;
  native let iconTagIds: array<TweakDBID>;
  native let exDataFlags: Uint32;
  native let mappinReferencePointId: scnReferencePointId;
}
