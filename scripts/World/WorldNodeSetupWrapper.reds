public native class WorldNodeSetupWrapper {
    public native func GetNode() -> ref<worldNode>
    public native func GetTransform() -> Transform
    public native func GetScale() -> Vector3
    public native func GetGlobalNodeID() -> GlobalNodeID
    public native func GetProxyNodeID() -> GlobalNodeID
    public native func GetStreamingDistance() -> Float

    public native func SetTransform(value: Transform)
    public native func SetScale(value: Vector3)
    public native func SetGlobalNodeID(value: GlobalNodeID)
    public native func SetProxyNodeID(value: GlobalNodeID)
    public native func SetStreamingDistance(value: Float)
}
