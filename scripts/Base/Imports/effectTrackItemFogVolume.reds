public native class effectTrackItemFogVolume extends effectTrackItem {
  public native let priority: Uint8;
  public native let densityFalloff: Float;
  public native let blendFalloff: Float;
  public native let density: ref<IEvaluatorFloat>;
  public native let size: ref<IEvaluatorVector>;
  public native let color: ref<IEvaluatorColor>;
}
