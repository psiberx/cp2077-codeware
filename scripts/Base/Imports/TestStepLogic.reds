public native class TestStepLogic extends IScriptable {
  public native let maxExecutionTimeSec: Float;
  public native let executionTimeSec: Float;
  public native let paramsData: array<ParamData>;

  public final native func GetATUI()
  public final native func GetAudioFunctionalTests()
  public final native func GetFunctionalTestsGameSystem()
  public final native func GetGameInstance()
  public final native func GetNavigationFunctionalTests()
  public final native func GetOptionalParam()
  public final native func GetParam()
  public final native func GetPhysicsFunctionalTests()
  public final native func GetPlayerFunctionalTests()
  public final native func GetPlayerSystem()
  public final native func GetRenderingFunctionalTests()
  public final native func GetUIFunctionalTests()
  public final native func GetWorldFunctionalTests()
  public final native func RegisterToEntityEvents()
  public final native func ReturnResult()
  public final native func ReturnValue()
  public final native func SetParamTypes()
  public final native func StartTest()
}
