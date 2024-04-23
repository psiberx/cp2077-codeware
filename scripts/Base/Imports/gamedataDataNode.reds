public abstract native class gamedataDataNode extends ISerializable {
  native let nodeType: gamedataDataNodeType;
  native let fileName: String;
  native let parent: wref<gamedataDataNode>;
}
