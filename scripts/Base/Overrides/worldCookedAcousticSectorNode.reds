public native struct worldCookedAcousticSectorInnerNode {
    public native let data: ResourceAsyncRef; // raRef<AcousticDataResource>
    public native let inSectorCoordsX: Uint32;
    public native let inSectorCoordsY: Uint32;
    public native let inSectorCoordsZ: Uint32;
    public native let edgeMask: Uint8;
}

public native class worldCookedAcousticSectorNode extends worldCookedNode {
    public native let generatorId: Uint32;

    public native func GetInnerNodeCount() -> Int32
    public native func GetInnerNode(index: Int32) -> script_ref<worldCookedAcousticSectorInnerNode>
}
