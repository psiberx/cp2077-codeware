public native struct gameAttachmentSlotsReplicatedState {
  native let componentName: CName;
  native let enabled: Bool;

  native let stateVersion: Uint32;
  native let slots: array<gameAttachmentSlotReplicatedState>;
}
