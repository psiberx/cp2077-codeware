public native struct worldExtractedNodeSocket {
  native let name: CName;
  native let displayName: CName;
  native let position: Vector3;
  native let rotation: Quaternion;
  native let direction: Vector3;
  native let type: worldNodeSocketType;
  native let isSnapped: Bool;
  native let color: Color;
}
