public native class gameEffectObjectProvider_TargetingObjectsInCone extends EffectObjectProvider {
  native let filterData: ref<physicsFilterData>;
  native let queryPreset: QueryPreset;
  native let searchQuery: TargetSearchQuery;
  native let maxTargets: Uint32;
  native let usePlayerPosAndForward: Bool;
}
