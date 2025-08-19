public native struct scnInterruptionScenario {
  public native let id: scnInterruptionScenarioId;
  public native let name: CName;
  public native let queueName: CName;
  public native let enabled: Bool;
  public native let talkOnReturn: Bool;
  public native let playInterruptLine: Bool;
  public native let forcePlayReturnLine: Bool;
  public native let interruptionSpammingSafeguard: Bool;
  public native let playingLinesBehavior: scnInterruptReturnLinesBehavior;
  public native let postInterruptSignalTimeDelay: Float;
  public native let postReturnSignalTimeDelay: Float;
  public native let postInterruptSignalFactCondition: ref<scnInterruptFactConditionType>;
  public native let postReturnSignalFactCondition: ref<scnInterruptFactConditionType>;
  public native let interruptConditions: array<ref<scnIInterruptCondition>>;
  public native let returnConditions: array<ref<scnIReturnCondition>>;
}
