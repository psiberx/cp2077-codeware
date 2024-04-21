public native struct worldProxyBoundingBoxSyncParams {
  native let positiveAxis: worldProxyBBoxSyncOptions;
  native let negativeAxis: worldProxyBBoxSyncOptions;
  native let pullRange: Float;
  native let makeStackable: Bool;
  native let stackOffset: Vector3;
}
