public importonly native class PhysicalSkinnedMeshComponent extends entSkinnedMeshComponent {
  native let simulationType: physicsSimulationType;
  native let useResourceSimulationType: Bool;
  native let startInactive: Bool;
  native let filterDataSource: physicsFilterDataSource;

  public final native func CreatePhysicalBodyInterface()
}
