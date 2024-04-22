public native class worldStaticParticleNode extends worldNode {
  native let emissionRate: Float;
  native let particleSystem: ResourceAsyncRef; // raRef<CParticleSystem>
  native let forcedAutoHideDistance: Float;
  native let forcedAutoHideRange: Float;
}
