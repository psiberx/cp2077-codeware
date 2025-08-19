public native class questPhaseNodeDefinition extends questEmbeddedGraphNodeDefinition {
  public native let saveLock: Bool;
  public native let phaseResource: ResourceAsyncRef; // raRef<questQuestPhaseResource>
  public native let unfreezingTriggerNodeRef: NodeRef;
  public native let phaseInstancePrefabs: array<questQuestPrefabEntry>;
  public native let phaseGraph: ref<questGraphDefinition>;
}
