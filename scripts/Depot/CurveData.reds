public native struct CurvePointFloat {
    public native let point: Float;
    public native let value: Float;
}

public native struct CurveDataFloat {
    public static native func GetInterpolationType(self: script_ref<CurveDataFloat>) -> curveEInterpolationType
    public static native func SetInterpolationType(self: script_ref<CurveDataFloat>, type: curveEInterpolationType)
    public static native func GetLinkType(self: script_ref<CurveDataFloat>) -> curveESegmentsLinkType
    public static native func SetLinkType(self: script_ref<CurveDataFloat>, type: curveESegmentsLinkType)
    public static native func GetSize(self: script_ref<CurveDataFloat>) -> Uint32
    public static native func SetSize(self: script_ref<CurveDataFloat>, newSize: Uint32)
    public static native func GetPoint(self: script_ref<CurveDataFloat>, index: Uint32) -> CurvePointFloat
    public static native func GetPointValue(self: script_ref<CurveDataFloat>, index: Uint32, out point: Float, out value: Float)
    public static native func SetPoint(self: script_ref<CurveDataFloat>, index: Uint32, point: CurvePointFloat)
    public static native func SetPointValue(self: script_ref<CurveDataFloat>, index: Uint32, point: Float, value: Float)
}

public native struct CurvePointVector2 {
    public native let point: Float;
    public native let value: Vector2;
}

public native struct CurveDataVector2 {
    public static native func GetInterpolationType(self: script_ref<CurveDataVector2>) -> curveEInterpolationType
    public static native func SetInterpolationType(self: script_ref<CurveDataVector2>, type: curveEInterpolationType)
    public static native func GetLinkType(self: script_ref<CurveDataVector2>) -> curveESegmentsLinkType
    public static native func SetLinkType(self: script_ref<CurveDataVector2>, type: curveESegmentsLinkType)
    public static native func GetSize(self: script_ref<CurveDataVector2>) -> Uint32
    public static native func SetSize(self: script_ref<CurveDataVector2>, newSize: Uint32)
    public static native func GetPoint(self: script_ref<CurveDataVector2>, index: Uint32) -> CurvePointVector2;
    public static native func GetPointValue(self: script_ref<CurveDataVector2>, index: Uint32, out point: Float, out value: Vector2)
    public static native func SetPoint(self: script_ref<CurveDataVector2>, index: Uint32, point: CurvePointVector2)
    public static native func SetPointValue(self: script_ref<CurveDataVector2>, index: Uint32, point: Float, value: Vector2)
}

public native struct CurvePointVector3 {
    public native let point: Float;
    public native let value: Vector3;
}

public native struct CurveDataVector3 {
    public static native func GetInterpolationType(self: script_ref<CurveDataVector3>) -> curveEInterpolationType
    public static native func SetInterpolationType(self: script_ref<CurveDataVector3>, type: curveEInterpolationType)
    public static native func GetLinkType(self: script_ref<CurveDataVector3>) -> curveESegmentsLinkType
    public static native func SetLinkType(self: script_ref<CurveDataVector3>, type: curveESegmentsLinkType)
    public static native func GetSize(self: script_ref<CurveDataVector3>) -> Uint32
    public static native func SetSize(self: script_ref<CurveDataVector3>, newSize: Uint32)
    public static native func GetPoint(self: script_ref<CurveDataVector3>, index: Uint32) -> CurvePointVector3;
    public static native func GetPointValue(self: script_ref<CurveDataVector3>, index: Uint32, out point: Float, out value: Vector3)
    public static native func SetPoint(self: script_ref<CurveDataVector3>, index: Uint32, point: CurvePointVector3)
    public static native func SetPointValue(self: script_ref<CurveDataVector3>, index: Uint32, point: Float, value: Vector3)
}

public native struct CurvePointVector4 {
    public native let point: Float;
    public native let value: Vector4;
}

public native struct CurveDataVector4 {
    public static native func GetInterpolationType(self: script_ref<CurveDataVector4>) -> curveEInterpolationType
    public static native func SetInterpolationType(self: script_ref<CurveDataVector4>, type: curveEInterpolationType)
    public static native func GetLinkType(self: script_ref<CurveDataVector4>) -> curveESegmentsLinkType
    public static native func SetLinkType(self: script_ref<CurveDataVector4>, type: curveESegmentsLinkType)
    public static native func GetSize(self: script_ref<CurveDataVector4>) -> Uint32
    public static native func SetSize(self: script_ref<CurveDataVector4>, newSize: Uint32)
    public static native func GetPoint(self: script_ref<CurveDataVector4>, index: Uint32) -> CurvePointVector4;
    public static native func GetPointValue(self: script_ref<CurveDataVector4>, index: Uint32, out point: Float, out value: Vector4)
    public static native func SetPoint(self: script_ref<CurveDataVector4>, index: Uint32, point: CurvePointVector4)
    public static native func SetPointValue(self: script_ref<CurveDataVector4>, index: Uint32, point: Float, value: Vector4)
}

public native struct CurvePointHDRColor {
    public native let point: Float;
    public native let value: HDRColor;
}

public native struct CurveDataHDRColor {
    public static native func GetInterpolationType(self: script_ref<CurveDataHDRColor>) -> curveEInterpolationType
    public static native func SetInterpolationType(self: script_ref<CurveDataHDRColor>, type: curveEInterpolationType)
    public static native func GetLinkType(self: script_ref<CurveDataHDRColor>) -> curveESegmentsLinkType
    public static native func SetLinkType(self: script_ref<CurveDataHDRColor>, type: curveESegmentsLinkType)
    public static native func GetSize(self: script_ref<CurveDataHDRColor>) -> Uint32
    public static native func SetSize(self: script_ref<CurveDataHDRColor>, newSize: Uint32)
    public static native func GetPoint(self: script_ref<CurveDataHDRColor>, index: Uint32) -> CurvePointHDRColor;
    public static native func GetPointValue(self: script_ref<CurveDataHDRColor>, index: Uint32, out point: Float, out value: HDRColor)
    public static native func SetPoint(self: script_ref<CurveDataHDRColor>, index: Uint32, point: CurvePointHDRColor)
    public static native func SetPointValue(self: script_ref<CurveDataHDRColor>, index: Uint32, point: Float, value: HDRColor)
}
