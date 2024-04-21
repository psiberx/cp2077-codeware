public native class worldInstancedDestructibleMeshNode extends worldMeshNode {
  native let staticMesh: ResourceAsyncRef; // raRef<CMesh>
  native let staticMeshAppearance: CName;
  native let simulationType: physicsSimulationType;
  native let filterDataSource: physicsFilterDataSource;
  native let startInactive: Bool;
  native let turnDynamicOnImpulse: Bool;
  native let useAggregate: Bool;
  native let enableSelfCollisionInAggregate: Bool;
  native let isDestructible: Bool;
  native let damageThreshold: Float;
  native let damageEndurance: Float;
  native let accumulateDamage: Bool;
  native let impulseToDamage: Float;
  native let fracturingEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let idleEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let instanceTransforms: array<Transform>;
  native let cookedInstanceTransforms: worldTransformBuffer;
  native let isPierceable: Bool;
  native let isWorkspot: Bool;
  native let navigationSetting: NavGenNavigationSetting;
  native let useMeshNavmeshSettings: Bool;
  native let systemsToNotifyFlags: Uint16;
}
