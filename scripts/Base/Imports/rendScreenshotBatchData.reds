public native struct rendScreenshotBatchData {
  public native let batchPositionsPath: AbsolutePathSerializable;
  public native let delayTime: Float;
  public native let numberOfCoordinatesToDump: Uint32;
  public native let mergeScreenshots: Bool;
  public native let streamingObserverMode: rendEStreamingObserverMode;
}
