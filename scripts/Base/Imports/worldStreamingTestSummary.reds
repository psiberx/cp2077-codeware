public native class worldStreamingTestSummary extends ISerializable {
  public native let gameDefinition: String;
  public native let noCrowds: Bool;
  public native let testDurationSeconds: Float;
  public native let initialBytesRead: Uint64;
  public native let bytesReadDuringTest: Uint64;
  public native let bytesReadDuringDriving: Uint64;
  public native let bytesReadDuringCooldown: Uint64;
  public native let totalSeeksBytes: Uint64;
  public native let minFps: Float;
  public native let maxFps: Float;
  public native let averageFps: Float;
}
