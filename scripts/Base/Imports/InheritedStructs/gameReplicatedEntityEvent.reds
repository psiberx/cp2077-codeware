public native struct gameReplicatedEntityEvent {
  native let entity: wref<Entity>;
  native let netTime: netTime;
  native let value: ref<Event>;
}
