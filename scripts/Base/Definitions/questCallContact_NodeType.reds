public native class questCallContact_NodeType extends questIPhoneManagerNodeType {
  native let caller: ref<gameJournalPath>;
  native let addressee: ref<gameJournalPath>;
  native let phase: questPhoneCallPhase;
  native let mode: questPhoneCallMode;
  native let prefabNodeRef: NodeRef;
  native let applyPhoneRestriction: Bool;
  native let isRejectable: Bool;
  native let showAvatar: Bool;
  native let visuals: questPhoneCallVisuals;
}
