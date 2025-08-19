public abstract native class gamedataDataNode extends ISerializable {
  public native let nodeType: gamedataDataNodeType;
  public native let fileName: String;
  public native let parent: wref<gamedataDataNode>;
}
