public native class worldOffMeshSmartObjectUserData extends worldOffMeshUserData {
  native let nodeTransform: WorldTransform;
  native let localSpaceTrajectoryStartPoint: Vector3;
  native let localSpaceTrajectoryEndPoint: Vector3;
  native let smartObjectDefinition: ref<gameSmartObjectDefinition>;
  native let type: worldOffMeshConnectionType;
}
