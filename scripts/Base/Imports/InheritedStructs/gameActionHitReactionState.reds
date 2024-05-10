public native struct gameActionHitReactionState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;
  native let animFeature: ref<AnimFeature_HitReactionsData>;
}
