public native class scnSceneResource extends CResource {
  native let entryPoints: array<scnEntryPoint>;
  native let exitPoints: array<scnExitPoint>;
  native let notablePoints: array<scnNotablePoint>;
  native let executionTagEntries: array<scnExecutionTagEntry>;
  native let actors: array<scnActorDef>;
  native let playerActors: array<scnPlayerActorDef>;
  native let sceneGraph: ref<scnSceneGraph>;
  native let localMarkers: array<scnLocalMarker>;
  native let props: array<scnPropDef>;
  native let ridResources: array<scnRidResourceHandler>;
  native let workspots: array<ref<scnWorkspotData>>;
  native let workspotInstances: array<scnWorkspotInstance>;
  native let resouresReferences: scnSRRefCollection;
  native let screenplayStore: scnscreenplayStore;
  native let locStore: scnlocLocStoreEmbedded;
  native let version: Uint32;
  native let voInfo: array<scnSceneVOInfo>;
  native let effectDefinitions: array<scnEffectDef>;
  native let effectInstances: array<scnEffectInstance>;
  native let executionTags: array<scnExecutionTag>;
  native let referencePoints: array<scnReferencePointDef>;
  native let interruptionScenarios: array<scnInterruptionScenario>;
  native let sceneSolutionHash: scnSceneSolutionHash;
  native let sceneCategoryTag: scnSceneCategoryTag;
  native let debugSymbols: scnDebugSymbols;
}
