public native class CDistantLightsResourceEntryWrapper {
    public native func GetColor() -> Color
    public native func SetColor(value: Color)
    public native func GetIntensity() -> Float
    public native func SetIntensity(value: Float)
    public native func GetField08() -> Float
    public native func SetField08(value: Float)
    public native func GetField0A() -> Float
    public native func SetField0A(value: Float)
    public native func GetDirX() -> Float
    public native func SetDirX(value: Float)
    public native func GetDirY() -> Float
    public native func SetDirY(value: Float)
    public native func GetPosX() -> Float
    public native func SetPosX(value: Float)
    public native func GetPosY() -> Float
    public native func SetPosY(value: Float)
    public native func GetPosZ() -> Float
    public native func SetPosZ(value: Float)
    public native func IsZFlip() -> Bool
    public native func SetZFlip(value: Bool)
    public native func GetAngle() -> Float
    public native func SetAngle(value: Float)
}

public native class CDistantLightsResource extends resStreamedResource {
    public native func GetEntryCount() -> Int32
    public native func GetEntry(index: Int32) -> ref<CDistantLightsResourceEntryWrapper>
}
