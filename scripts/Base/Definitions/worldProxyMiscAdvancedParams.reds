public native struct worldProxyMiscAdvancedParams {
  native let useLod1: Bool;
  native let smoothVolume: Bool;
  native let blurCutout: Uint8;
  native let occlusionRatio: Uint8;
  native let capTop: Bool;
  native let capBottom: Bool;
  native let fillHolesBeforeReduceRatio: Float;
  native let fillHolesAfterReduceRatio: Float;
  native let rsSweepOrder: Int32;
  native let rsDetailDrop: Float;
  native let rsAxisPrecision: Vector3;
  native let rsAxisExpand: Vector3;
  native let rsAliasingReduction: Float;
  native let bcMergeRange: Float;
  native let bcSizeCutoff: Float;
  native let bcIterations: Float;
  native let bcMaxSize: Float;
  native let bcMinSize: Float;
  native let bcMergeSensitivity: Float;
  native let bcMinScale: Float;
  native let bcGridSize: Float;
  native let bcFilterSensitivity: Float;
  native let bcBoundsRatioLimit: Float;
  native let useClosestPointOnMesh: Bool;
  native let removeIslands: Bool;
  native let backgroundColor: Color;
}
