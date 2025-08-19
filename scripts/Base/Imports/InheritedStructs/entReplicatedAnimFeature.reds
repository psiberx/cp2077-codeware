public native struct entReplicatedAnimFeature {
  public native let entity: wref<Entity>;
  public native let netTime: netTime;
  public native let name: CName;
  public native let value: ref<AnimFeature>;
  public native let invokeCallback: Bool;
}
