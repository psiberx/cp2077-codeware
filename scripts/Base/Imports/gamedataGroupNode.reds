public native class gamedataGroupNode extends gamedataDataNode {
  public native let name: String;
  public native let base: String;
  public native let schema: String;
  public native let isInline: Bool;
  public native let baseGroup: wref<gamedataGroupNode>;
  public native let schemaGroup: wref<gamedataGroupNode>;
  public native let package: wref<gamedataPackageNode>;
  public native let fileNode: ref<gamedataFileNode>;
  public native let inlineGroupId: Uint32;
  public native let inheritanceState: gamedataGroupNodeInheritanceState;
  public native let serializedVariables: array<gamedataGroupNodeGroupVariable>;
  public native let tags: array<CName>;
}
