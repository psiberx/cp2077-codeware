@addField(ProjectileComponent)
public native let onCollisionAction: gameprojectileOnCollisionAction;

@addField(ProjectileComponent)
public native let useSweepCollision: Bool;

@addField(ProjectileComponent)
public native let collisionsFilterClosest: Bool;

@addField(ProjectileComponent)
public native let sweepCollisionRadius: Float;

@addField(ProjectileComponent)
public native let rotationOffset: Quaternion;

@addField(ProjectileComponent)
public native let deriveOwnerVelocity: Bool;

@addField(ProjectileComponent)
public native let derivedVelocityParams: gameprojectileVelocityParams;

@addField(ProjectileComponent)
public native let filterData: ref<physicsFilterData>;

@addField(ProjectileComponent)
public native let queryPreset: QueryPreset;

@addField(ProjectileComponent)
public native let previewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
public native let bouncePreviewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
public native let explosionPreviewEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(ProjectileComponent)
public native let explosionPreviewTime: Float;

@addField(ProjectileComponent)
public native let gameEffectRef: EffectRef;
