public abstract importonly class PhysicalTriggerComponent extends IPlacedComponent {
  public native let simulationType: physicsSimulationType;
  public native let shape: physicsTriggerShape;
  public native let filterData: ref<physicsFilterData>;
  public native let isEnabled: Bool;
}
