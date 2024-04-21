public native class gamemountingMountingFacilitySharedState extends ISerializable {
  native let children: array<wref<Entity>>;
  native let parents: array<wref<Entity>>;
  native let slotIds: array<MountingSlotId>;
  native let parentTypes: array<gameMountingObjectType>;
  native let childTypes: array<gameMountingObjectType>;
}
