public native class rendSingleScreenShotData extends ISerializable {
  native let mode: rendScreenshotMode;
  native let outputPath: AbsolutePathSerializable;
  native let resolution: renddimEPreset;
  native let resolutionMultiplier: rendResolutionMultiplier;
  native let emmModes: array<EEnvManagerModifier>;
  native let forceLOD0: Bool;
  native let saveFormat: ESaveFormat;
}
