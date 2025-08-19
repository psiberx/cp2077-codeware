@neverRef()
public native class navgendebugHeightfield extends ISerializable {
  public native let bounds: Box;
  public native let cellSize: Float;
  public native let cellHeight: Float;
  public native let width: Uint16;
  public native let height: Uint16;
  public native let rawSpans: navgendebugSpansData;
  public native let compactSpans: navgendebugSpansData;
  public native let cells: array<navgendebugCompactCell>;
  public native let regions: array<Uint16>;
  public native let distancefield: array<Uint16>;
  public native let maxDistancefieldValue: Uint16;
}
