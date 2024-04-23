public native struct worldTriggerAreaEventInfo {
  native let nodeInstance: ref<worldTriggerAreaNodeInstance>;
  native let eventWorldPosition: Vector3;
  native let numActivatorsInArea: Uint32;
  native let activatorID: Uint32;
}
