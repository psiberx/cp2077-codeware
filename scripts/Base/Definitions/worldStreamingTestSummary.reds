public native class worldStreamingTestSummary extends ISerializable {
  native let gameDefinition: String;
  native let noCrowds: Bool;
  native let testDurationSeconds: Float;
  native let initialBytesRead: Uint64;
  native let bytesReadDuringTest: Uint64;
  native let bytesReadDuringDriving: Uint64;
  native let bytesReadDuringCooldown: Uint64;
  native let totalSeeksBytes: Uint64;
  native let minFps: Float;
  native let maxFps: Float;
  native let averageFps: Float;
}
