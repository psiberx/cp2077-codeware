public native struct worldStreamingSectorDescriptor {
  native let data: ResourceAsyncRef; // raRef<worldStreamingSector>
  native let streamingBox: Box;
  native let questPrefabNodeRef: NodeRef;
  native let numNodeRanges: Uint32;
  native let variants: array<worldStreamingSectorVariant>;
  native let blockIndex: worldStreamingBlockIndex;
  native let level: Uint8;
  native let category: worldStreamingSectorCategory;
}
