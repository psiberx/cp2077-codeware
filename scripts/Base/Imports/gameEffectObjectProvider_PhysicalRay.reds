public native class gameEffectObjectProvider_PhysicalRay extends EffectObjectProvider {
  public native let inputPosition: EffectInputParameter_Vector;
  public native let inputForward: EffectInputParameter_Vector;
  public native let inputRange: EffectInputParameter_Float;
  public native let outputRaycastEnd: EffectOutputParameter_Vector;
  public native let filterData: ref<physicsFilterData>;
  public native let queryPreset: QueryPreset;
}
