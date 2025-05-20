public importonly class PhysicalSkinnedMeshComponent extends entSkinnedMeshComponent {
  native let simulationType: physicsSimulationType;
  native let useResourceSimulationType: Bool;
  native let startInactive: Bool;
  native let filterDataSource: physicsFilterDataSource;
  native let filterData: ref<physicsFilterData>;

  public final native func CreatePhysicalBodyInterface()
}
