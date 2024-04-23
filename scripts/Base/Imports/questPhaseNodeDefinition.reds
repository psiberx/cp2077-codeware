public native class questPhaseNodeDefinition extends questEmbeddedGraphNodeDefinition {
  native let saveLock: Bool;
  native let phaseResource: ResourceAsyncRef; // raRef<questQuestPhaseResource>
  native let unfreezingTriggerNodeRef: NodeRef;
  native let phaseInstancePrefabs: array<questQuestPrefabEntry>;
  native let phaseGraph: ref<questGraphDefinition>;
}
