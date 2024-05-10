public native struct entReplicatedAnimFeature {
  native let entity: wref<Entity>;
  native let netTime: netTime;
  native let name: CName;
  native let value: ref<AnimFeature>;
  native let invokeCallback: Bool;
}
