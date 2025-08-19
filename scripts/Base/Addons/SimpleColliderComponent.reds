@addField(SimpleColliderComponent)
public native let isEnabled: Bool;

@addField(SimpleColliderComponent)
public native let colliders: array<ref<physicsICollider>>;

@addField(SimpleColliderComponent)
public native let filter: ref<physicsFilterData>;
