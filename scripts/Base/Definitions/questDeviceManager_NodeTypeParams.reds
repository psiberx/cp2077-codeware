public native class questDeviceManager_NodeTypeParams extends ISerializable {
  native let objectRef: NodeRef;
  native let slotName: CName;
  native let entityRef: EntityReference;
  native let deviceControllerClass: CName;
  native let deviceAction: CName;
  native let actionProperties: array<questDeviceManager_ActionProperty>;
}
