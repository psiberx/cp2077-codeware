public native class worldInstancedDestructibleMeshNode extends worldMeshNode {
  public native let staticMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let staticMeshAppearance: CName;
  public native let simulationType: physicsSimulationType;
  public native let filterDataSource: physicsFilterDataSource;
  public native let startInactive: Bool;
  public native let turnDynamicOnImpulse: Bool;
  public native let useAggregate: Bool;
  public native let enableSelfCollisionInAggregate: Bool;
  public native let isDestructible: Bool;
  public native let filterData: ref<physicsFilterData>;
  public native let damageThreshold: Float;
  public native let damageEndurance: Float;
  public native let accumulateDamage: Bool;
  public native let impulseToDamage: Float;
  public native let fracturingEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let idleEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let instanceTransforms: array<Transform>;
  public native let cookedInstanceTransforms: worldTransformBuffer;
  public native let isPierceable: Bool;
  public native let isWorkspot: Bool;
  public native let navigationSetting: NavGenNavigationSetting;
  public native let useMeshNavmeshSettings: Bool;
  public native let systemsToNotifyFlags: Uint16;
}
