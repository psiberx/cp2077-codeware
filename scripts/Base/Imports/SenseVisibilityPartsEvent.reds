public native class SenseVisibilityPartsEvent extends Event {
  public native let target: wref<GameObject>;
  public native let isPrimaryVisible: Bool;
  public native let isSecondaryVisible: Bool;
  public native let description: CName;
}
