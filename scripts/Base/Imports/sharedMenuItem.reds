public native struct sharedMenuItem {
  public native let id: CName;
  public native let displayName: String;
  public native let tooltip: String;
  public native let subItems: array<sharedMenuItem>;
  public native let isEnabled: Bool;
  public native let type: sharedMenuItemType;
  public native let isChecked: Bool;
  public native let checkGroup: String;
}
