@addField(MinigameLogicController)
native let startHealth: Uint32;

@addField(MinigameLogicController)
native let playerLibraryName: CName;

@addField(MinigameLogicController)
native let playerColliderPositionOffset: Vector2;

@addField(MinigameLogicController)
native let playerColliderSizeOffset: Vector2;

@addField(MinigameLogicController)
native let gameplayRoot: inkCompoundRef;

@addField(MinigameLogicController)
native let baseSpeed: Float;

@addField(MinigameLogicController)
native let spawnedListLibraryNames: array<CName>;
