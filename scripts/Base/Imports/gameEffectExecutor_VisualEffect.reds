public native class gameEffectExecutor_VisualEffect extends EffectExecutor {
  native let effect: ResourceAsyncRef; // raRef<worldEffect>
  native let attached: Bool;
  native let breakLoopOnDetach: Bool;
  native let effectTag: CName;
  native let vectorEvaluator: ref<gameEffectVectorEvaluator>;
}
