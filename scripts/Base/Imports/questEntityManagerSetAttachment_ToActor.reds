public native class questEntityManagerSetAttachment_ToActor extends questIEntityManagerSetAttachment_NodeSubType {
  native let attachmentRef: NodeRef;
  native let objectRef: EntityReference;
  native let isPlayer: Bool;
  native let slot: CName;
  native let offsetMode: questAttachmentOffsetMode;
  native let customOffsetPos: Vector3;
  native let customOffsetRot: Quaternion;
}
