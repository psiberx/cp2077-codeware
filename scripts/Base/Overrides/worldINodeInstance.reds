public abstract native class worldINodeInstance extends ISerializable {
    public native func GetNode() -> ref<worldNode>
    public native func GetTransform() -> Transform
    public native func GetScale() -> Vector3
    public native func GetGlobalNodeID() -> GlobalNodeID
    public native func GetProxyNodeID() -> GlobalNodeID
    public native func GetStreamingDistance() -> Float
}
