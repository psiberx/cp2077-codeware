public native struct rendScreenshotBatchData {
  native let batchPositionsPath: AbsolutePathSerializable;
  native let delayTime: Float;
  native let numberOfCoordinatesToDump: Uint32;
  native let mergeScreenshots: Bool;
  native let streamingObserverMode: rendEStreamingObserverMode;
}
