public native struct worldStreamingSectorDescriptor {
  public native let data: ResourceAsyncRef; // raRef<worldStreamingSector>
  public native let streamingBox: Box;
  public native let questPrefabNodeRef: NodeRef;
  public native let numNodeRanges: Uint32;
  public native let variants: array<worldStreamingSectorVariant>;
  public native let blockIndex: worldStreamingBlockIndex;
  public native let level: Uint8;
  public native let category: worldStreamingSectorCategory;
}
