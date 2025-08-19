public native class gamedataVariableNode extends gamedataDataNode {
  public native let hashedName: CName;
  public native let type: String;
  public native let name: String;
  public native let isForeignKey: Bool;
  public native let isArray: Bool;
  public native let hasArrayValues: Bool;
  public native let isAddition: Bool;
  public native let typeEnum: gamedataTweakDBType;
  public native let values: array<gamedataVariableNodeVariableValue>;
}
