public native class gamedataGroupNode extends gamedataDataNode {
  native let name: String;
  native let base: String;
  native let schema: String;
  native let isInline: Bool;
  native let inlineGroupId: Uint32;
  native let inheritanceState: gamedataGroupNodeInheritanceState;
  native let serializedVariables: array<gamedataGroupNodeGroupVariable>;
  native let tags: array<CName>;
}
