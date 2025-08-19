public native class gamedataFileNode extends gamedataDataNode {
  public native let packageName: String;
  public native let packageDependencies: [wref<gamedataPackageNode>; 16];
  public native let package: wref<gamedataPackageNode>;
  public native let variables: array<ref<gamedataVariableNode>>;
  public native let groups: array<ref<gamedataGroupNode>>;
}
