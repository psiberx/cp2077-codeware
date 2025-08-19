public native struct rendCaptureParameters {
  public native let enable: Bool;
  public native let mode: rendScreenshotMode;
  public native let videoRecordingMode: Bool;
  public native let audioRecordingMode: Bool;
  public native let emmModes: array<EEnvManagerModifier>;
  public native let initialFrameNumber: Uint32;
  public native let outputDirectoryIndex: Uint32;
  public native let outputDirectoryName: String;
  public native let outputDirectoryNameSuffix: String;
  public native let recordingFPS: Uint32;
  public native let customResolution: Point;
  public native let resolutionMultiplier: rendResolutionMultiplier;
  public native let outputPath: AbsolutePathSerializable;
  public native let fovMultiplier: Float;
  public native let captureContextType: rendCaptureContextType;
  public native let saveFormat: ESaveFormat;
}
