public native struct worldProxySurfaceFlattenParams {
  native let flatten: Bool;
  native let groupingStepAngle: worldProxyNormalAngleStepSize;
  native let syncNormalSource: worldProxySyncNormalSource;
  native let coreAxisRotationOffset: Float;
  native let postFlattenReduce: Bool;
}
