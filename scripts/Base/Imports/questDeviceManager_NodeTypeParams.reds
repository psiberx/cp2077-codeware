public native class questDeviceManager_NodeTypeParams extends ISerializable {
  public native let objectRef: NodeRef;
  public native let slotName: CName;
  public native let entityRef: EntityReference;
  public native let deviceControllerClass: CName;
  public native let deviceAction: CName;
  public native let actionProperties: array<questDeviceManager_ActionProperty>;
}
