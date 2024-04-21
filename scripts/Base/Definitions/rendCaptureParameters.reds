public native struct rendCaptureParameters {
  native let enable: Bool;
  native let mode: rendScreenshotMode;
  native let videoRecordingMode: Bool;
  native let audioRecordingMode: Bool;
  native let emmModes: array<EEnvManagerModifier>;
  native let initialFrameNumber: Uint32;
  native let outputDirectoryIndex: Uint32;
  native let outputDirectoryName: String;
  native let outputDirectoryNameSuffix: String;
  native let recordingFPS: Uint32;
  native let customResolution: Point;
  native let resolutionMultiplier: rendResolutionMultiplier;
  native let outputPath: AbsolutePathSerializable;
  native let fovMultiplier: Float;
  native let captureContextType: rendCaptureContextType;
  native let saveFormat: ESaveFormat;
}
