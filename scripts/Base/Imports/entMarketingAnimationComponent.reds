public native class entMarketingAnimationComponent extends IPlacedComponent {
  native let freezeAnimations: Bool;
  native let animations: array<entMarketingAnimationEntry>;
  native let enableLookAt: Bool;
  native let lookAtSettings: ref<animLookAtPreset_FullControl>;
  native let lookAtCamera: Bool;
  native let lookAtOrbitDistance: Float;
  native let lookAtTargetPitch: Float;
  native let lookAtTargetYaw: Float;
}
