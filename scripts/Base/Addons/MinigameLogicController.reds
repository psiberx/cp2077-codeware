@addField(MinigameLogicController)
public native let startHealth: Uint32;

@addField(MinigameLogicController)
public native let playerLibraryName: CName;

@addField(MinigameLogicController)
public native let playerColliderPositionOffset: Vector2;

@addField(MinigameLogicController)
public native let playerColliderSizeOffset: Vector2;

@addField(MinigameLogicController)
public native let gameplayRoot: inkCompoundRef;

@addField(MinigameLogicController)
public native let baseSpeed: Float;

@addField(MinigameLogicController)
public native let spawnedListLibraryNames: array<CName>;
