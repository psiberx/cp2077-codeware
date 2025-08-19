public native class gameEffectExecutor_GroundSlamEffects extends EffectExecutor {
  public native let groundEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let waterEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let earthquakeLevel1: ResourceAsyncRef; // raRef<worldEffect>
  public native let earthquakeLevel2: ResourceAsyncRef; // raRef<worldEffect>
  public native let earthquakeLevel1ChargeThreshold: Float;
  public native let earthquakeLevel2ChargeThreshold: Float;
}
