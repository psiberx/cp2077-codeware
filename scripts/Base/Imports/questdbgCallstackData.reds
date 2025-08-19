public native struct questdbgCallstackData {
  public native let resourceHash: Uint64;
  public native let phases: array<questdbgCallstackPhase>;
  public native let blocks: array<questdbgCallstackBlock>;
  public native let executed: array<Uint64>;
  public native let executedHistory: array<Uint64>;
  public native let failed: array<Uint64>;
  public native let callstackRevision: Uint32;
}
