@addField(ColliderComponent)
native let colliders: array<ref<physicsICollider>>;

@addField(ColliderComponent)
native let simulationType: physicsSimulationType;

@addField(ColliderComponent)
native let startInactive: Bool;

@addField(ColliderComponent)
native let useCCD: Bool;

@addField(ColliderComponent)
native let massOverride: Float;

@addField(ColliderComponent)
native let volume: Float;

@addField(ColliderComponent)
native let mass: Float;

@addField(ColliderComponent)
native let inertia: Vector3;

@addField(ColliderComponent)
native let comOffset: Transform;

@addField(ColliderComponent)
native let filterData: ref<physicsFilterData>;

@addField(ColliderComponent)
native let isEnabled: Bool;

@addField(ColliderComponent)
native let dynamicTrafficSetting: TrafficGenDynamicTrafficSetting;
