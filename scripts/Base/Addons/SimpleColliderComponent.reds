@addField(SimpleColliderComponent)
native let isEnabled: Bool;

@addField(SimpleColliderComponent)
native let colliders: array<ref<physicsICollider>>;

@addField(SimpleColliderComponent)
native let filter: ref<physicsFilterData>;
