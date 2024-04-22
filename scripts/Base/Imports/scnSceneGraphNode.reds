public abstract native class scnSceneGraphNode extends ISerializable {
  native let nodeId: scnNodeId;
  native let ffStrategy: scnFastForwardStrategy;
  native let outputSockets: array<scnOutputSocket>;
}
