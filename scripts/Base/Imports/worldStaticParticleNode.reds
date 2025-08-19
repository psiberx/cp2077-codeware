public native class worldStaticParticleNode extends worldNode {
  public native let emissionRate: Float;
  public native let particleSystem: ResourceAsyncRef; // raRef<CParticleSystem>
  public native let forcedAutoHideDistance: Float;
  public native let forcedAutoHideRange: Float;
}
