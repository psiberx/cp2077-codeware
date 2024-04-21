public importonly native class ReactionComponent extends IComponent {
  native let reactions: array<ReactionData>;
  native let triggerAutomatically: Bool;

  public final native func GetReactionIndex()
  public final native func GetRequiredItems()
  public final native func PerformReaction()
  public final native func PerformReactionWithIK()
  public final native func SetCanceled()
  public final native func SetFinished()
}
