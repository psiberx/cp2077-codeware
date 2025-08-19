public native class entMarketingAnimationComponent extends IPlacedComponent {
  public native let freezeAnimations: Bool;
  public native let animations: array<entMarketingAnimationEntry>;
  public native let enableLookAt: Bool;
  public native let lookAtSettings: ref<animLookAtPreset_FullControl>;
  public native let lookAtCamera: Bool;
  public native let lookAtOrbitDistance: Float;
  public native let lookAtTargetPitch: Float;
  public native let lookAtTargetYaw: Float;
}
