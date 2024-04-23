public native class effectTrackItemFogVolume extends effectTrackItem {
  native let priority: Uint8;
  native let densityFalloff: Float;
  native let blendFalloff: Float;
  native let density: ref<IEvaluatorFloat>;
  native let size: ref<IEvaluatorVector>;
  native let color: ref<IEvaluatorColor>;
}
