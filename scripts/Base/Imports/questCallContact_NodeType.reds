public native class questCallContact_NodeType extends questIPhoneManagerNodeType {
  public native let caller: ref<gameJournalPath>;
  public native let addressee: ref<gameJournalPath>;
  public native let phase: questPhoneCallPhase;
  public native let mode: questPhoneCallMode;
  public native let prefabNodeRef: NodeRef;
  public native let applyPhoneRestriction: Bool;
  public native let isRejectable: Bool;
  public native let showAvatar: Bool;
  public native let visuals: questPhoneCallVisuals;
}
