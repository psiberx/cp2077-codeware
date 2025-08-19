public native class worldStaticSoundEmitterNode extends worldNode {
  public native let radius: Float;
  public native let audioName: CName;
  public native let Settings: ref<audioAmbientAreaSettings>;
  public native let usePhysicsObstruction: Bool;
  public native let occlusionEnabled: Bool;
  public native let acousticRepositioningEnabled: Bool;
  public native let obstructionChangeTime: Float;
  public native let useDoppler: Bool;
  public native let dopplerFactor: Float;
  public native let setOpenDoorEmitter: Bool;
  public native let emitterMetadataName: CName;
  public native let overrideRolloff: Bool;
  public native let rolloffOverride: Float;
  public native let ambientPaletteTag: CName;
}
