public native class scnSectionNode extends scnSceneGraphNode {
  public native let events: array<ref<scnSceneEvent>>;
  public native let sectionDuration: scnSceneTime;
  public native let actorBehaviors: array<scnSectionInternalsActorBehavior>;
  public native let isFocusClue: Bool;
}
