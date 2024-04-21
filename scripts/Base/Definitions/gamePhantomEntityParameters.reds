public native struct gamePhantomEntityParameters {
  native let teleportStartEffect: CName;
  native let teleportEndEffect: CName;
  native let spawnEffect: CName;
  native let glitchEffect: CName;
  native let phantomVisibleStates: array<gamePhantomEntityState>;
  native let blendableAppearanceMatches: array<gamePhantomEntityParametersBlendableAppearanceMatch>;
}
