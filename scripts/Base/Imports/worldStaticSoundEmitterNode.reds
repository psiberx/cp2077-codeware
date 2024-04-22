public native class worldStaticSoundEmitterNode extends worldNode {
  native let radius: Float;
  native let audioName: CName;
  native let usePhysicsObstruction: Bool;
  native let occlusionEnabled: Bool;
  native let acousticRepositioningEnabled: Bool;
  native let obstructionChangeTime: Float;
  native let useDoppler: Bool;
  native let dopplerFactor: Float;
  native let setOpenDoorEmitter: Bool;
  native let emitterMetadataName: CName;
  native let overrideRolloff: Bool;
  native let rolloffOverride: Float;
  native let ambientPaletteTag: CName;
}
