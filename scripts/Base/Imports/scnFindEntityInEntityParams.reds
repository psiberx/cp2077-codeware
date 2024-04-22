public native struct scnFindEntityInEntityParams {
  native let actorId: scnActorId;
  native let performerId: scnPerformerId;
  native let itemID: TweakDBID;
  native let slotID: TweakDBID;
  native let forceMaxVisibility: Bool;
  native let ownershipTransferOptions: scnPropOwnershipTransferOptions;
}
