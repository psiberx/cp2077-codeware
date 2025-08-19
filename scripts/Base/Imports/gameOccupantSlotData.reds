public importonly struct gameOccupantSlotData {
  public native let slotName: CName;
  public native let syncAnimationTag: CName;
  public native let workSpotResource: ResourceRef; // rRef<workWorkspotResource>
  public native let exitOffsetFromSlot: Vector4;
  public native let role: gameMountingSlotRole;
}
