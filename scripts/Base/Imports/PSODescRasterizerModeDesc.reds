public native struct PSODescRasterizerModeDesc {
  public native let wireframe: Bool;
  public native let frontWinding: PSODescRasterizerModeFrontFaceWinding;
  public native let cullMode: PSODescRasterizerModeCullMode;
  public native let allowMSAA: Bool;
  public native let conservativeRasterization: Bool;
  public native let offsetMode: PSODescRasterizerModeOffsetMode;
  public native let scissors: Bool;
  public native let valid: Bool;
}
