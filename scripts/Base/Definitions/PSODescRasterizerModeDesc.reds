public native struct PSODescRasterizerModeDesc {
  native let wireframe: Bool;
  native let frontWinding: PSODescRasterizerModeFrontFaceWinding;
  native let cullMode: PSODescRasterizerModeCullMode;
  native let allowMSAA: Bool;
  native let conservativeRasterization: Bool;
  native let offsetMode: PSODescRasterizerModeOffsetMode;
  native let scissors: Bool;
  native let valid: Bool;
}
