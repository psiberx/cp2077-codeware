public importonly class PhysicalSkinnedMeshComponent extends entSkinnedMeshComponent {
  public native let simulationType: physicsSimulationType;
  public native let useResourceSimulationType: Bool;
  public native let startInactive: Bool;
  public native let filterDataSource: physicsFilterDataSource;
  public native let filterData: ref<physicsFilterData>;

  public final native func CreatePhysicalBodyInterface()
}
