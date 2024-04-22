public native class AIDefTreeVariableComparison extends LibTreeDefTreeVariableBoolBase {
  native let exportAsProperty: Bool;
  native let referenceVariableId: Uint16;
  native let referenceVariableName: CName;
  native let referenceVariableShortName: CName;
  native let referenceType: CName;
  native let operator: EComparisonType;
  native let referenceValue: Variant;
}
