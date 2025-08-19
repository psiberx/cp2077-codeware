public native struct gameMountDescriptor {
  public native let parentId: EntityID;
  public native let slotName: CName;
  public native let initialTransform: Transform;
  public native let state: PuppetVehicleState;
  public native let mountType: MountDescriptor_MountingType;
}
