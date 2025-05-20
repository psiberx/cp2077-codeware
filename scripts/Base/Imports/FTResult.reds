public importonly struct FTResult {
  native let code: FunctionalTestsResultCode;
  native let msg: String;

  public final static native func IsValid()
  public final static native func Make()
  public final static native func MakeValid()
  public final static native func SetResult()
}
