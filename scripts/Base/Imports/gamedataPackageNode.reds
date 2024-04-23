public native class gamedataPackageNode extends ISerializable {
  native let name: String;
  native let serializedVariables: array<ref<gamedataVariableNode>>;
  native let serializedGroups: array<ref<gamedataGroupNode>>;
  native let files: array<ref<gamedataFileNode>>;
}
