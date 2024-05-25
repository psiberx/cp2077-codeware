public native struct scnLookAtEventData {
  native let id: Uint32;
  native let enable: Bool;
  native let singleBodyPartName: CName;
  native let singleTargetSlot: CName;
  native let bodyTargetSlot: CName;
  native let headTargetSlot: CName;
  native let eyesTargetSlot: CName;
  native let singleWeight: Float;
  native let bodyWeight: Float;
  native let headWeight: Float;
  native let eyesWeight: Float;
  native let useSingleWeightCurve: Bool;
  native let useBodyWeightCurve: Bool;
  native let useHeadWeightCurve: Bool;
  native let useEyesWeightCurve: Bool;
  native let singleWeightCurve: CurveDataFloat;
  native let bodyWeightCurve: CurveDataFloat;
  native let headWeightCurve: CurveDataFloat;
  native let eyesWeightCurve: CurveDataFloat;
  native let singleLimits: LookAtLimits;
  native let bodyLimits: LookAtLimits;
  native let headLimits: LookAtLimits;
  native let eyesLimits: LookAtLimits;
}
