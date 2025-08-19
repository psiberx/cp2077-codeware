public native struct questdbgCallstackPhase {
  public native let id: Uint64;
  public native let parentId: Uint64;
  public native let phases: array<Uint64>;
  public native let blocks: array<Uint64>;
}
