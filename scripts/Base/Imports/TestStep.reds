public native class TestStep extends IScriptable {
  public native let stepName: CName;
  public native let scriptId: Uint16;
  public native let reproStep: String;
  public native let args: array<Variant>;
  public native let stepTimeout: Float;
  public native let stopTestOnFailure: Bool;

  public final native func Param()
  public final native func SetStepLogic()
}
