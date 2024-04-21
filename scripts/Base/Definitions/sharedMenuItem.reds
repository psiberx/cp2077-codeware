public native struct sharedMenuItem {
  native let id: CName;
  native let displayName: String;
  native let tooltip: String;
  native let subItems: array<sharedMenuItem>;
  native let isEnabled: Bool;
  native let type: sharedMenuItemType;
  native let isChecked: Bool;
  native let checkGroup: String;
}
