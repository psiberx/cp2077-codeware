public native class gamedataPackageNode extends ISerializable {
  public native let name: String;
  public native let serializedVariables: array<ref<gamedataVariableNode>>;
  public native let serializedGroups: array<ref<gamedataGroupNode>>;
  public native let files: array<ref<gamedataFileNode>>;
}
