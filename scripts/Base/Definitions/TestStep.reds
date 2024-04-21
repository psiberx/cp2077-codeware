public native class TestStep extends IScriptable {
  native let stepName: CName;
  native let scriptId: Uint16;
  native let reproStep: String;
  native let args: array<Variant>;
  native let stepTimeout: Float;
  native let stopTestOnFailure: Bool;

  public final native func Param()
  public final native func SetStepLogic()
}
