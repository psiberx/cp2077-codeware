public native struct questdbgCallstackData {
  native let resourceHash: Uint64;
  native let phases: array<questdbgCallstackPhase>;
  native let blocks: array<questdbgCallstackBlock>;
  native let executed: array<Uint64>;
  native let executedHistory: array<Uint64>;
  native let failed: array<Uint64>;
  native let callstackRevision: Uint32;
}
