public native struct audioAudParameter {
  native let name: CName;
  native let value: Float;
  native let enterCurveType: audioESoundCurveType;
  native let enterCurveTime: Float;
  native let exitCurveType: audioESoundCurveType;
  native let exitCurveTime: Float;
}
