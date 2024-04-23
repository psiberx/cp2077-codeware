public native class FunctionalTestsDataMemoryStatsData extends ISerializable {
  native let totalPhysicalMemory: Uint64;
  native let availablePhysicalMemory: Uint64;
  native let runtimeTotalBytesAllocated: Uint64;
  native let cpuBytesAllocated: Uint64;
  native let gpuBytesAllocated: Uint64;
  native let totalAllocationCount: Uint32;
  native let cpuAllocationCount: Uint32;
  native let gpuAllocationCount: Uint32;
  native let engineTick: Uint64;
  native let lastTimeDelta: Float;
  native let engineTime: Double;
  native let rawLocalTime: Uint64;
  native let playerPosition: String;
  native let playerOrientation: String;
  native let poolsRuntimeInfo: array<FunctionalTestsDataMemoryPoolRuntimeData>;
  native let poolsCurrentInfo: array<FunctionalTestsDataMemoryPoolStaticData>;
}
