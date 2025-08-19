public native struct gamePhantomEntityParameters {
  public native let teleportStartEffect: CName;
  public native let teleportEndEffect: CName;
  public native let spawnEffect: CName;
  public native let glitchEffect: CName;
  public native let phantomVisibleStates: array<gamePhantomEntityState>;
  public native let blendableAppearanceMatches: array<gamePhantomEntityParametersBlendableAppearanceMatch>;
}
