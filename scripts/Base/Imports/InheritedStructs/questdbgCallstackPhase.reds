public native struct questdbgCallstackPhase {
  native let id: Uint64;
  native let parentId: Uint64;
  native let phases: array<Uint64>;
  native let blocks: array<Uint64>;
}
