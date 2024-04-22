public native class gamedataVariableNode extends gamedataDataNode {
  native let hashedName: CName;
  native let type: String;
  native let name: String;
  native let isForeignKey: Bool;
  native let isArray: Bool;
  native let hasArrayValues: Bool;
  native let isAddition: Bool;
  native let typeEnum: gamedataTweakDBType;
  native let values: array<gamedataVariableNodeVariableValue>;
}
