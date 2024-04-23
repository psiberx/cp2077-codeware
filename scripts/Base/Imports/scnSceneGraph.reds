public native class scnSceneGraph extends ISerializable {
  native let graph: array<ref<scnSceneGraphNode>>;
  native let startNodes: array<scnNodeId>;
  native let endNodes: array<scnNodeId>;
}
