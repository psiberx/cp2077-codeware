public importonly native struct gameOccupantSlotData {
  native let slotName: CName;
  native let syncAnimationTag: CName;
  native let workSpotResource: ResourceRef;
  native let exitOffsetFromSlot: Vector4;
  native let role: gameMountingSlotRole;
}
