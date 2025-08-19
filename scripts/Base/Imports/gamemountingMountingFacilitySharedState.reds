public native class gamemountingMountingFacilitySharedState extends ISerializable {
  public native let children: array<wref<Entity>>;
  public native let parents: array<wref<Entity>>;
  public native let slotIds: array<MountingSlotId>;
  public native let parentTypes: array<gameMountingObjectType>;
  public native let childTypes: array<gameMountingObjectType>;
}
