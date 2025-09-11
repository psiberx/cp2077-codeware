public native class entParticlesComponent extends IVisualComponent {
  public native let emissionRate: Float;
  public native let particleSystem: ResourceRef; // rRef<CParticleSystem>
  public native let autoHideRange: Float;
  public native let renderLayerMask: Uint8; // RenderSceneLayerMask
  public native let isEnabled: Bool;
}
