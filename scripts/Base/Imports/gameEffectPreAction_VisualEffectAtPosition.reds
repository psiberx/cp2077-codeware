public native class gameEffectPreAction_VisualEffectAtPosition extends EffectPreAction {
  native let effect: ResourceAsyncRef; // raRef<worldEffect>
  native let attached: Bool;
  native let breakLoopOnDetach: Bool;
  native let vertical: Bool;
  native let effectTag: CName;
}
