public native struct scnInterruptionScenario {
  native let id: scnInterruptionScenarioId;
  native let name: CName;
  native let queueName: CName;
  native let enabled: Bool;
  native let talkOnReturn: Bool;
  native let playInterruptLine: Bool;
  native let forcePlayReturnLine: Bool;
  native let interruptionSpammingSafeguard: Bool;
  native let playingLinesBehavior: scnInterruptReturnLinesBehavior;
  native let postInterruptSignalTimeDelay: Float;
  native let postReturnSignalTimeDelay: Float;
  native let postInterruptSignalFactCondition: ref<scnInterruptFactConditionType>;
  native let postReturnSignalFactCondition: ref<scnInterruptFactConditionType>;
  native let interruptConditions: array<ref<scnIInterruptCondition>>;
  native let returnConditions: array<ref<scnIReturnCondition>>;
}
