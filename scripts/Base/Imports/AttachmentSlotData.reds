public native struct AttachmentSlotData {
  native let slotID: TweakDBID;
  native let itemObject: ref<ItemObject>;
  native let activeItemID: ItemID;
  native let prevItemID: ItemID;
  native let appearanceItemID: ItemID;
}
