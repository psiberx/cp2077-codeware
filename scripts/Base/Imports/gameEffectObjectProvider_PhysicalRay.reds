public native class gameEffectObjectProvider_PhysicalRay extends EffectObjectProvider {
  native let inputPosition: EffectInputParameter_Vector;
  native let inputForward: EffectInputParameter_Vector;
  native let inputRange: EffectInputParameter_Float;
  native let outputRaycastEnd: EffectOutputParameter_Vector;
  native let queryPreset: QueryPreset;
}
