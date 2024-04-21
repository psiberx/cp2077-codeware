public native class SenseVisibilityPartsEvent extends Event {
  native let target: wref<GameObject>;
  native let isPrimaryVisible: Bool;
  native let isSecondaryVisible: Bool;
  native let description: CName;
}
