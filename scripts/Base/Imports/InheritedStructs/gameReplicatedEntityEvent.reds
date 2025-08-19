public native struct gameReplicatedEntityEvent {
  public native let entity: wref<Entity>;
  public native let netTime: netTime;
  public native let value: ref<Event>;
}
