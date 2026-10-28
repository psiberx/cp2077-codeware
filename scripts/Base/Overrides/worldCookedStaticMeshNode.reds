public native class worldCookedStaticMeshNode extends worldCookedMeshNode {
    public native func GetInnerNodeCount() -> Int32
    public native func GetInnerNode(index: Int32) -> script_ref<worldCookedMeshInnerNode>
}
