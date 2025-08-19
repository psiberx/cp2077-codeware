public native class questAddRemoveItem_NodeTypeParams extends ISerializable {
  public native let sendNotification: Bool;
  public native let isPlayer: Bool;
  public native let objectRef: EntityReference;
  public native let entityRef: ref<questUniversalRef>;
  public native let nodeType: questEAddRemoveItemType;
  public native let itemID: TweakDBID;
  public native let quantity: Int32;
  public native let flagItemAddedCallbackAsSilent: Bool;
  public native let removeAllQuantity: Bool;
  public native let tagToRemove: CName;
  public native let itemIDsToIgnoreOnRemove: array<TweakDBID>;
  public native let tagsToIgnoreOnRemove: array<CName>;
}
