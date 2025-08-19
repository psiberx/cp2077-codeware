public native class worldFoliageBakedDestructionMapping extends worldFoliageDestructionMapping {
  public native let numFrames: Float;
  public native let frameRate: Float;
  public native let audioMetadata: CName;
  public native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let filterDataSource: physicsFilterDataSource;
  public native let filterData: ref<physicsFilterData>;
}
