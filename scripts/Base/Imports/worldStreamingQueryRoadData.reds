public native struct worldStreamingQueryRoadData {
  native let transform: Transform;
  native let splineData: ref<Spline>;
  native let roadGlobalNodeId: GlobalNodeID;
  native let totalRoadWidth: Float;
  native let connectedRoadsStartIndex: Uint16;
  native let connectedRoadsCount: Uint16;
}
