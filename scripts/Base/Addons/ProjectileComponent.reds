@addField(ProjectileComponent)
native let onCollisionAction: gameprojectileOnCollisionAction;

@addField(ProjectileComponent)
native let useSweepCollision: Bool;

@addField(ProjectileComponent)
native let collisionsFilterClosest: Bool;

@addField(ProjectileComponent)
native let sweepCollisionRadius: Float;

@addField(ProjectileComponent)
native let rotationOffset: Quaternion;

@addField(ProjectileComponent)
native let deriveOwnerVelocity: Bool;

@addField(ProjectileComponent)
native let derivedVelocityParams: gameprojectileVelocityParams;

@addField(ProjectileComponent)
native let filterData: ref<physicsFilterData>;

@addField(ProjectileComponent)
native let queryPreset: QueryPreset;

@addField(ProjectileComponent)
native let previewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
native let bouncePreviewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
native let explosionPreviewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
native let explosionPreviewTime: Float;

@addField(ProjectileComponent)
native let gameEffectRef: EffectRef;
