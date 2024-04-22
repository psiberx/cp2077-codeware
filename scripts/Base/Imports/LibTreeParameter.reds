public native struct LibTreeParameter {
  native let parameterName: CName;
  native let parameterId: Uint16;
  native let parameterType: LibTreeEParameterType;
  native let value: Variant;
}
