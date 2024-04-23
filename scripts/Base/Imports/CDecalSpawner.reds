public native class CDecalSpawner extends ISerializable {
  native let materialStatic: ResourceRef; // rRef<IMaterial>
  native let materialSkinned: ResourceRef; // rRef<IMaterial>
  native let specularColor: Color;
  native let specularScale: Float;
  native let specularBase: Float;
  native let roughnessScale: Float;
  native let normalThreshold: Float;
  native let additiveNormals: Bool;
  native let diffuseRandomColor0: Color;
  native let diffuseRandomColor1: Color;
  native let subUVType: ERenderDynamicDecalAtlas;
  native let specularity: Float;
  native let farZ: Float;
  native let nearZ: Float;
  native let size: ref<IEvaluatorFloat>;
  native let depthFadePower: Float;
  native let normalFadeBias: Float;
  native let normalFadeScale: Float;
  native let doubleSided: Bool;
  native let projectionMode: ERenderDynamicDecalProjection;
  native let decalLifetime: ref<IEvaluatorFloat>;
  native let decalFadeTime: Float;
  native let decalFadeInTime: Float;
  native let projectOnStatic: Bool;
  native let projectOnSkinned: Bool;
  native let startScale: Float;
  native let scaleTime: Float;
  native let useVerticalProjection: Bool;
  native let spawnPriority: EDynamicDecalSpawnPriority;
  native let autoHideDistance: Float;
}
