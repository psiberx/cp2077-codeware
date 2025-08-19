public native class rendSingleScreenShotData extends ISerializable {
  public native let mode: rendScreenshotMode;
  public native let outputPath: AbsolutePathSerializable;
  public native let resolution: renddimEPreset;
  public native let resolutionMultiplier: rendResolutionMultiplier;
  public native let emmModes: array<EEnvManagerModifier>;
  public native let forceLOD0: Bool;
  public native let saveFormat: ESaveFormat;
}
