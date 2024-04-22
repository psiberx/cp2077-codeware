public native class questEventManagerNodeDefinition extends questDisableableNodeDefinition {
  native let isUiEvent: Bool;
  native let isObjectPlayer: Bool;
  native let objectRef: EntityReference;
  native let managerName: String;
  native let event: ref<IScriptable>;
  native let PSClassName: CName;
  native let componentName: CName;
}
