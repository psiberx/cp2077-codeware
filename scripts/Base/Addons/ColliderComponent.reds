@addField(ColliderComponent)
public native let colliders: array<ref<physicsICollider>>;

@addField(ColliderComponent)
public native let simulationType: physicsSimulationType;

@addField(ColliderComponent)
public native let startInactive: Bool;

@addField(ColliderComponent)
public native let useCCD: Bool;

@addField(ColliderComponent)
public native let massOverride: Float;

@addField(ColliderComponent)
public native let volume: Float;

@addField(ColliderComponent)
public native let mass: Float;

@addField(ColliderComponent)
public native let inertia: Vector3;

@addField(ColliderComponent)
public native let comOffset: Transform;

@addField(ColliderComponent)
public native let filterData: ref<physicsFilterData>;

@addField(ColliderComponent)
public native let isEnabled: Bool;

@addField(ColliderComponent)
public native let dynamicTrafficSetting: TrafficGenDynamicTrafficSetting;
