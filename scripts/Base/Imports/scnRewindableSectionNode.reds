public native class scnRewindableSectionNode extends scnSceneGraphNode {
  native let events: array<ref<scnSceneEvent>>;
  native let sectionDuration: scnSceneTime;
  native let actorBehaviors: array<scnSectionInternalsActorBehavior>;
  native let playSpeedModifiers: scnRewindableSectionPlaySpeedModifiers;
}
