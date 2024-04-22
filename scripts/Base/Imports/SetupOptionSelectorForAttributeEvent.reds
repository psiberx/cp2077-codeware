public native class SetupOptionSelectorForAttributeEvent extends Event {
  native let attribute: Uint32;
  native let values: array<PhotoModeOptionSelectorData>;
  native let startDataValue: Int32;
  native let doApply: Bool;
}
