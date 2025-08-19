public native class scnSceneResource extends CResource {
  public native let entryPoints: array<scnEntryPoint>;
  public native let exitPoints: array<scnExitPoint>;
  public native let notablePoints: array<scnNotablePoint>;
  public native let executionTagEntries: array<scnExecutionTagEntry>;
  public native let actors: array<scnActorDef>;
  public native let playerActors: array<scnPlayerActorDef>;
  public native let sceneGraph: ref<scnSceneGraph>;
  public native let localMarkers: array<scnLocalMarker>;
  public native let props: array<scnPropDef>;
  public native let ridResources: array<scnRidResourceHandler>;
  public native let workspots: array<ref<scnWorkspotData>>;
  public native let workspotInstances: array<scnWorkspotInstance>;
  public native let resouresReferences: scnSRRefCollection;
  public native let screenplayStore: scnscreenplayStore;
  public native let locStore: scnlocLocStoreEmbedded;
  public native let version: Uint32;
  public native let voInfo: array<scnSceneVOInfo>;
  public native let effectDefinitions: array<scnEffectDef>;
  public native let effectInstances: array<scnEffectInstance>;
  public native let executionTags: array<scnExecutionTag>;
  public native let referencePoints: array<scnReferencePointDef>;
  public native let interruptionScenarios: array<scnInterruptionScenario>;
  public native let sceneSolutionHash: scnSceneSolutionHash;
  public native let sceneCategoryTag: scnSceneCategoryTag;
  public native let debugSymbols: scnDebugSymbols;
}
