public importonly native struct gameOccupantSlotData {
  native let slotName: CName;
  native let syncAnimationTag: CName;
  native let workSpotResource: ResourceRef; // rRef<workWorkspotResource>
  native let exitOffsetFromSlot: Vector4;
  native let role: gameMountingSlotRole;
}
