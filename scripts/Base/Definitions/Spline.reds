public native class Spline extends ISerializable {
  native let points: array<SplinePoint>;
  native let looped: Bool;
  native let reversed: Bool;
  native let hasDirection: Bool;
}
