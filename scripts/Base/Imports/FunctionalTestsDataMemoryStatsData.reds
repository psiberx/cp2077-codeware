public native class FunctionalTestsDataMemoryStatsData extends ISerializable {
  public native let totalPhysicalMemory: Uint64;
  public native let availablePhysicalMemory: Uint64;
  public native let runtimeTotalBytesAllocated: Uint64;
  public native let cpuBytesAllocated: Uint64;
  public native let gpuBytesAllocated: Uint64;
  public native let totalAllocationCount: Uint32;
  public native let cpuAllocationCount: Uint32;
  public native let gpuAllocationCount: Uint32;
  public native let engineTick: Uint64;
  public native let lastTimeDelta: Float;
  public native let engineTime: Double;
  public native let rawLocalTime: Uint64;
  public native let playerPosition: String;
  public native let playerOrientation: String;
  public native let poolsRuntimeInfo: array<FunctionalTestsDataMemoryPoolRuntimeData>;
  public native let poolsCurrentInfo: array<FunctionalTestsDataMemoryPoolStaticData>;
}
