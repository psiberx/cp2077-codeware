public native class gamedataFileNode extends gamedataDataNode {
  native let packageName: String;
  native let packageDependencies: [wref<gamedataPackageNode>; 16];
  native let package: wref<gamedataPackageNode>;
  native let variables: array<ref<gamedataVariableNode>>;
  native let groups: array<ref<gamedataGroupNode>>;
}
