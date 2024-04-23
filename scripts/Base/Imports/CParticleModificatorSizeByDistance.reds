public native class CParticleModificatorSizeByDistance extends IParticleModificator {
  native let nearDistanceRangeStart: ref<IEvaluatorFloat>;
  native let nearDistanceRangeEnd: ref<IEvaluatorFloat>;
  native let nearDistanceSizeMultiplier: ref<IEvaluatorFloat>;
  native let farDistanceRangeStart: ref<IEvaluatorFloat>;
  native let farDistanceRangeEnd: ref<IEvaluatorFloat>;
  native let farDistanceSizeMultiplier: ref<IEvaluatorFloat>;
}
