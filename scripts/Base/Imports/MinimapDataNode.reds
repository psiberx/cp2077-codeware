public native class MinimapDataNode extends worldNode {
  public native let encodedShapesRef: ResourceAsyncRef; // raRef<minimapEncodedShapes>
  public native let streamingDistance: Float;
  public native let localBounds: Box;
  public native let allInteriorShapes: Bool;
}
