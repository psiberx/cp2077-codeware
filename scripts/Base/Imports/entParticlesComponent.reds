public native class entParticlesComponent extends IVisualComponent {
  native let emissionRate: Float;
  native let particleSystem: ResourceRef; // rRef<CParticleSystem>
  native let autoHideRange: Float;
  native let isEnabled: Bool;
}
