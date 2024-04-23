public abstract importonly native class PhysicalTriggerComponent extends IPlacedComponent {
  native let simulationType: physicsSimulationType;
  native let shape: physicsTriggerShape;
  native let filterData: ref<physicsFilterData>;
  native let isEnabled: Bool;
}
