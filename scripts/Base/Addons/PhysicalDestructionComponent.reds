@addField(PhysicalDestructionComponent)
native let mesh: ResourceAsyncRef; // raRef<CMesh>

@addField(PhysicalDestructionComponent)
native let meshAppearance: CName;

@addField(PhysicalDestructionComponent)
native let forceAutoHideDistance: Float;

@addField(PhysicalDestructionComponent)
native let destructionParams: physicsDestructionParams;

@addField(PhysicalDestructionComponent)
native let destructionLevelData: array<physicsDestructionLevelData>;

@addField(PhysicalDestructionComponent)
native let isEnabled: Bool;

@addField(PhysicalDestructionComponent)
native let audioMetadata: CName;

@addField(PhysicalDestructionComponent)
native let systemsToNotifyFlags: Uint16;
