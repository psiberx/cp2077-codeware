public native class audioAmbientAreaNotifier extends worldITriggerAreaNotifer {
  native let Settings: ref<audioAmbientAreaSettings>;
  native let usePhysicsObstruction: Bool;
  native let occlusionEnabled: Bool;
  native let acousticRepositioningEnabled: Bool;
  native let obstructionChangeTime: Float;
  native let overrideRolloff: Bool;
  native let rolloffOverride: Float;
  native let useAutoOutdoorness: Bool;
}
