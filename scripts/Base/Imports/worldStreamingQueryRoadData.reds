public native struct worldStreamingQueryRoadData {
  public native let transform: Transform;
  public native let splineData: ref<Spline>;
  public native let roadGlobalNodeId: GlobalNodeID;
  public native let totalRoadWidth: Float;
  public native let connectedRoadsStartIndex: Uint16;
  public native let connectedRoadsCount: Uint16;
}
