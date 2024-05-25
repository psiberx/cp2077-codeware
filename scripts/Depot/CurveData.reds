
public native struct CurvePointFloat {
    public native let point: Float;
    public native let value: Float;
}

public native struct CurveDataFloat {
    public static native func GetSize(self: script_ref<CurveDataFloat>) -> Uint32;
    public static native func GetPoint(self: script_ref<CurveDataFloat>, index: Uint32) -> CurvePointFloat;
    public static native func GetPointValue(self: script_ref<CurveDataFloat>, index: Uint32, out point: Float, out value: Float) -> Void;
    public static native func SetPoint(self: script_ref<CurveDataFloat>, index: Uint32, point: CurvePointFloat) -> Void;
    public static native func SetPointValue(self: script_ref<CurveDataFloat>, index: Uint32, point: Float, value: Float) -> Void;
}

public native struct CurvePointVector2 {
    public native let point: Float;
    public native let value: Vector2;
}

public native struct CurveDataVector2 {
    public static native func GetSize(self: script_ref<CurveDataVector2>) -> Uint32;
    public static native func GetPoint(self: script_ref<CurveDataVector2>, index: Uint32) -> CurvePointVector2;
    public static native func GetPointValue(self: script_ref<CurveDataVector2>, index: Uint32, out point: Float, out value: Vector2) -> Void;
    public static native func SetPoint(self: script_ref<CurveDataVector2>, index: Uint32, point: CurvePointVector2) -> Void;
    public static native func SetPointValue(self: script_ref<CurveDataVector2>, index: Uint32, point: Float, value: Vector2) -> Void;
}

public native struct CurvePointVector3 {
    public native let point: Float;
    public native let value: Vector3;
}

public native struct CurveDataVector3 {
    public static native func GetSize(self: script_ref<CurveDataVector3>) -> Uint32;
    public static native func GetPoint(self: script_ref<CurveDataVector3>, index: Uint32) -> CurvePointVector3;
    public static native func GetPointValue(self: script_ref<CurveDataVector3>, index: Uint32, out point: Float, out value: Vector3) -> Void;
    public static native func SetPoint(self: script_ref<CurveDataVector3>, index: Uint32, point: CurvePointVector3) -> Void;
    public static native func SetPointValue(self: script_ref<CurveDataVector3>, index: Uint32, point: Float, value: Vector3) -> Void;
}

public native struct CurvePointVector4 {
    public native let point: Float;
    public native let value: Vector4;
}

public native struct CurveDataVector4 {
    public static native func GetSize(self: script_ref<CurveDataVector4>) -> Uint32;
    public static native func GetPoint(self: script_ref<CurveDataVector4>, index: Uint32) -> CurvePointVector4;
    public static native func GetPointValue(self: script_ref<CurveDataVector4>, index: Uint32, out point: Float, out value: Vector4) -> Void;
    public static native func SetPoint(self: script_ref<CurveDataVector4>, index: Uint32, point: CurvePointVector4) -> Void;
    public static native func SetPointValue(self: script_ref<CurveDataVector4>, index: Uint32, point: Float, value: Vector4) -> Void;
}

public native struct CurvePointHDRColor {
    public native let point: Float;
    public native let value: HDRColor;
}

public native struct CurveDataHDRColor {
    public static native func GetSize(self: script_ref<CurveDataHDRColor>) -> Uint32;
    public static native func GetPoint(self: script_ref<CurveDataHDRColor>, index: Uint32) -> CurvePointHDRColor;
    public static native func GetPointValue(self: script_ref<CurveDataHDRColor>, index: Uint32, out point: Float, out value: HDRColor) -> Void;
    public static native func SetPoint(self: script_ref<CurveDataHDRColor>, index: Uint32, point: CurvePointHDRColor) -> Void;
    public static native func SetPointValue(self: script_ref<CurveDataHDRColor>, index: Uint32, point: Float, value: HDRColor) -> Void;
}
