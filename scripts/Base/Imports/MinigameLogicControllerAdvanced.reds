public abstract native class MinigameLogicControllerAdvanced extends inkLogicController {
  public native let playerLibraryName: CName;
  public native let playerColliderPositionOffset: Vector2;
  public native let playerColliderSizeOffset: Vector2;
  public native let gameplayRoot: inkCompoundRef;
  public native let baseSpeed: Float;
  public native let layers: array<inkWidgetRef>;
  public native let cheatCodes: array<SideScrollerCheatCodeAdvanced>;
  public native let acceptableCheatKeys: array<CName>;

  public final native func FinishGame()
}
