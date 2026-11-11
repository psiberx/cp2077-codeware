public native class CDistantLightsResourceEntryWrapper {
    public native func GetColor() -> Color
    public native func SetColor(value: Color)
    public native func GetField03() -> Uint8
    public native func SetField03(value: Uint8)
    public native func GetIntensity() -> Float
    public native func SetIntensity(value: Float)
    public native func GetRadius() -> Float
    public native func SetRadius(value: Float)
    public native func GetFadeDistance() -> Float
    public native func SetFadeDistance(value: Float)
    public native func GetField0C() -> Uint16
    public native func SetField0C(value: Uint16)
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
    public native func HasZFlip() -> Bool
    public native func SetZFlip(value: Bool)
    public native func HasFlag141() -> Bool
    public native func SetFlag141(value: Bool)
    public native func HasFlag142() -> Bool
    public native func SetFlag142(value: Bool)
    public native func HasFlag143() -> Bool
    public native func SetFlag143(value: Bool)
    public native func GetAngle() -> Float
    public native func SetAngle(value: Float)
}

public native class CDistantLightsResource extends resStreamedResource {
    public native func GetEntryCount() -> Int32
    public native func GetEntry(index: Int32) -> ref<CDistantLightsResourceEntryWrapper>
}
