public native class gameEffectExecutor_GroundSlamEffects extends EffectExecutor {
  native let groundEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let waterEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let earthquakeLevel1: ResourceAsyncRef; // raRef<worldEffect>
  native let earthquakeLevel2: ResourceAsyncRef; // raRef<worldEffect>
  native let earthquakeLevel1ChargeThreshold: Float;
  native let earthquakeLevel2ChargeThreshold: Float;
}
