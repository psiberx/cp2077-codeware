public importonly native class entRenderHighlightEvent extends Event {
  native let fillIndex: Uint8;
  native let outlineIndex: Uint8;
  native let seeThroughWalls: Bool;
  native let componentName: CName;
  native let opacity: Float;
}
