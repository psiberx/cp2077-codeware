public native struct gameBodyTypeAnimationDefinition {
  public native let rig: ResourceAsyncRef; // raRef<animRig>
  public native let animsets: array<ResourceAsyncRef>;
  public native let overrides: array<gameAnimationOverrideDefinition>;
}
