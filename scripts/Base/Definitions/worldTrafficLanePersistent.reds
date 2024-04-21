public native struct worldTrafficLanePersistent {
  native let outLanes: array<worldTrafficConnectivityOutLane>;
  native let inLanes: array<worldTrafficConnectivityInLane>;
  native let outline: array<Vector3>;
  native let accumulatedLengths: array<Float>;
  native let crowdCreationInfo: worldTrafficLaneCrowdCreationInfo;
  native let maxSpeed: Uint8;
  native let deadEndStart: Float;
  native let length: Float;
  native let width: Float;
  native let area: Float;
  native let flags: Uint16;
  native let subGraphId: Uint16;
  native let playerGPSInfo: worldTrafficLanePlayerGPSInfo;
  native let neighborGroupIndex: Uint16;
  native let nodeRefHash: Uint64;
  native let laneNumber: Uint16;
  native let seqNumber: Uint16;
  native let isReversed: Bool;
  native let roadMaterials: array<worldRoadMaterialInfo>;
  native let polygon: array<Vector2>;
}
