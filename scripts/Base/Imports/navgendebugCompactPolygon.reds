@neverRef()
public native class navgendebugCompactPolygon extends ISerializable {
  native let index: Uint16;
  native let indices: array<Uint16>;
  native let neighbors: array<Uint16>;
  native let area: Uint8;
  native let region: Uint16;
  native let flags: Uint16;
}
