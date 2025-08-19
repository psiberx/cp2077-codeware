public native class questEntityManagerSetAttachment_ToActor extends questIEntityManagerSetAttachment_NodeSubType {
  public native let attachmentRef: NodeRef;
  public native let objectRef: EntityReference;
  public native let isPlayer: Bool;
  public native let slot: CName;
  public native let offsetMode: questAttachmentOffsetMode;
  public native let customOffsetPos: Vector3;
  public native let customOffsetRot: Quaternion;
}
