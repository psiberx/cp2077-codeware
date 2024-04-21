public native struct gameMountDescriptor {
  native let parentId: EntityID;
  native let slotName: CName;
  native let initialTransform: Transform;
  native let state: PuppetVehicleState;
  native let mountType: MountDescriptor_MountingType;
}
