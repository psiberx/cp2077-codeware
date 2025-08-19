@addField(PhysicalDestructionComponent)
public native let mesh: ResourceAsyncRef; // raRef<CMesh>

@addField(PhysicalDestructionComponent)
public native let meshAppearance: CName;

@addField(PhysicalDestructionComponent)
public native let forceAutoHideDistance: Float;

@addField(PhysicalDestructionComponent)
public native let destructionParams: physicsDestructionParams;

@addField(PhysicalDestructionComponent)
public native let destructionLevelData: array<physicsDestructionLevelData>;

@addField(PhysicalDestructionComponent)
public native let isEnabled: Bool;

@addField(PhysicalDestructionComponent)
public native let audioMetadata: CName;

@addField(PhysicalDestructionComponent)
public native let systemsToNotifyFlags: Uint16;
