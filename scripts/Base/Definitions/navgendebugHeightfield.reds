public native class navgendebugHeightfield extends ISerializable {
  native let bounds: Box;
  native let cellSize: Float;
  native let cellHeight: Float;
  native let width: Uint16;
  native let height: Uint16;
  native let rawSpans: navgendebugSpansData;
  native let compactSpans: navgendebugSpansData;
  native let cells: array<navgendebugCompactCell>;
  native let regions: array<Uint16>;
  native let distancefield: array<Uint16>;
  native let maxDistancefieldValue: Uint16;
}
