public native struct gameTransformAnimationDefinition {
  native let name: CName;
  native let autoStart: Bool;
  native let autoStartDelay: Float;
  native let timesToPlay: Uint32;
  native let looping: Bool;
  native let timeScale: Float;
  native let reverse: Bool;
  native let timeline: gameTransformAnimationTimeline;
}
