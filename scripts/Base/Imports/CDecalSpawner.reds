public native class CDecalSpawner extends ISerializable {
  public native let materialStatic: ResourceRef; // rRef<IMaterial>
  public native let materialSkinned: ResourceRef; // rRef<IMaterial>
  public native let specularColor: Color;
  public native let specularScale: Float;
  public native let specularBase: Float;
  public native let roughnessScale: Float;
  public native let normalThreshold: Float;
  public native let additiveNormals: Bool;
  public native let diffuseRandomColor0: Color;
  public native let diffuseRandomColor1: Color;
  public native let subUVType: ERenderDynamicDecalAtlas;
  public native let specularity: Float;
  public native let farZ: Float;
  public native let nearZ: Float;
  public native let size: ref<IEvaluatorFloat>;
  public native let depthFadePower: Float;
  public native let normalFadeBias: Float;
  public native let normalFadeScale: Float;
  public native let doubleSided: Bool;
  public native let projectionMode: ERenderDynamicDecalProjection;
  public native let decalLifetime: ref<IEvaluatorFloat>;
  public native let decalFadeTime: Float;
  public native let decalFadeInTime: Float;
  public native let projectOnStatic: Bool;
  public native let projectOnSkinned: Bool;
  public native let startScale: Float;
  public native let scaleTime: Float;
  public native let useVerticalProjection: Bool;
  public native let spawnPriority: EDynamicDecalSpawnPriority;
  public native let autoHideDistance: Float;
}
