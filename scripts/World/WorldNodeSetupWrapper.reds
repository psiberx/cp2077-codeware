public native class WorldNodeSetupWrapper {
    public native func GetNodeIndex() -> Uint16
    public native func GetNode() -> ref<worldNode>
    public native func GetTransform() -> Transform
    public native func GetPosition() -> Vector4
    public native func GetOrientation() -> Quaternion
    public native func GetScale() -> Vector3
    public native func GetNodeRef() -> NodeRef
    public native func GetGlobalNodeID() -> GlobalNodeID
    public native func GetProxyNodeID() -> GlobalNodeID
    public native func GetStreamingPosition() -> Vector3
    public native func GetStreamingDistance() -> Float
    public native func GetSecondaryRefPointPosition() -> Vector3
    public native func GetSecondaryRefPointDistance() -> Float

    public native func SetNodeIndex(value: Uint16)
    public native func SetTransform(value: Transform)
    public native func SetPosition(value: Vector4)
    public native func SetOrientation(value: Quaternion)
    public native func SetScale(value: Vector3)
    public native func SetNodeRef(value: NodeRef)
    public native func SetGlobalNodeID(value: GlobalNodeID)
    public native func SetProxyNodeID(value: GlobalNodeID)
    public native func SetStreamingPosition(value: Vector3)
    public native func SetStreamingDistance(value: Float)
    public native func SetSecondaryRefPointPosition(value: Vector3)
    public native func SetSecondaryRefPointDistance(value: Float)
}
