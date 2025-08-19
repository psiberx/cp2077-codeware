public native class questEventManagerNodeDefinition extends questDisableableNodeDefinition {
  public native let isUiEvent: Bool;
  public native let isObjectPlayer: Bool;
  public native let objectRef: EntityReference;
  public native let managerName: String;
  public native let event: ref<IScriptable>;
  public native let PSClassName: CName;
  public native let componentName: CName;
}
