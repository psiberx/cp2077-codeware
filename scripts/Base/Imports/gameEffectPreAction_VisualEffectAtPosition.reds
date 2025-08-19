public native class gameEffectPreAction_VisualEffectAtPosition extends EffectPreAction {
  public native let effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let attached: Bool;
  public native let breakLoopOnDetach: Bool;
  public native let vertical: Bool;
  public native let effectTag: CName;
}
