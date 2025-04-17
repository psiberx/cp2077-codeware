@addField(PhysicalMeshComponent)
native let visibilityAnimationParam: CName;

@addField(PhysicalMeshComponent)
native let simulationType: physicsSimulationType;

@addField(PhysicalMeshComponent)
native let useResourceSimulationType: Bool;

@addField(PhysicalMeshComponent)
native let startInactive: Bool;

@addField(PhysicalMeshComponent)
native let filterDataSource: physicsFilterDataSource;

@addField(PhysicalMeshComponent)
native let filterData: ref<physicsFilterData>;
