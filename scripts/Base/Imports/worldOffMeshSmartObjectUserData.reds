public native class worldOffMeshSmartObjectUserData extends worldOffMeshUserData {
  public native let nodeTransform: WorldTransform;
  public native let localSpaceTrajectoryStartPoint: Vector3;
  public native let localSpaceTrajectoryEndPoint: Vector3;
  public native let smartObjectDefinition: ref<gameSmartObjectDefinition>;
  public native let type: worldOffMeshConnectionType;
}
