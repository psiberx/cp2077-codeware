public native class worldFoliageBakedDestructionMapping extends worldFoliageDestructionMapping {
  native let numFrames: Float;
  native let frameRate: Float;
  native let audioMetadata: CName;
  native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let filterDataSource: physicsFilterDataSource;
}
