public native class questAddRemoveItem_NodeTypeParams extends ISerializable {
  native let sendNotification: Bool;
  native let isPlayer: Bool;
  native let objectRef: EntityReference;
  native let nodeType: questEAddRemoveItemType;
  native let itemID: TweakDBID;
  native let quantity: Int32;
  native let flagItemAddedCallbackAsSilent: Bool;
  native let removeAllQuantity: Bool;
  native let tagToRemove: CName;
  native let itemIDsToIgnoreOnRemove: array<TweakDBID>;
  native let tagsToIgnoreOnRemove: array<CName>;
}
