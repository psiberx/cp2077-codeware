public native struct gameBodyTypeAnimationDefinition {
  native let rig: ResourceAsyncRef; // raRef<animRig>
  native let animsets: array<ResourceAsyncRef>;
  native let overrides: array<gameAnimationOverrideDefinition>;
}
