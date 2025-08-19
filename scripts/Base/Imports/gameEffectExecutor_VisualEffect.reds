public native class gameEffectExecutor_VisualEffect extends EffectExecutor {
  public native let effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let attached: Bool;
  public native let breakLoopOnDetach: Bool;
  public native let effectTag: CName;
  public native let vectorEvaluator: ref<gameEffectVectorEvaluator>;
}
