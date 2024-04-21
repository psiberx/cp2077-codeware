public native class MinimapDataNode extends worldNode {
  native let encodedShapesRef: ResourceAsyncRef; // raRef<minimapEncodedShapes>
  native let streamingDistance: Float;
  native let localBounds: Box;
  native let allInteriorShapes: Bool;
}
