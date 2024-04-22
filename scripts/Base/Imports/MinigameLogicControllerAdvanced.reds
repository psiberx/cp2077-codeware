public abstract native class MinigameLogicControllerAdvanced extends inkLogicController {
  native let playerLibraryName: CName;
  native let playerColliderPositionOffset: Vector2;
  native let playerColliderSizeOffset: Vector2;
  native let gameplayRoot: inkCompoundRef;
  native let baseSpeed: Float;
  native let layers: array<inkWidgetRef>;
  native let cheatCodes: array<SideScrollerCheatCodeAdvanced>;
  native let acceptableCheatKeys: array<CName>;

  public final native func FinishGame()
}
