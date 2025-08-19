public native struct questdbgRuntimeData {
  public native let version: Uint64;
  public native let questResourcePathHash: Uint64;
  public native let selectedBlockId: Uint64;
  public native let objects: array<ref<ISerializable>>;
}
