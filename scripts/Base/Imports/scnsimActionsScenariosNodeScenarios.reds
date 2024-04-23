public native struct scnsimActionsScenariosNodeScenarios {
  native let nodeId: scnNodeId;
  native let scenarios: array<ref<scnsimIActionScenario>>;
  native let fallback: ref<scnsimIActionScenario>;
}
