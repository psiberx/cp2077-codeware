public native class AICTreeNodeActionAnimationCurvePathDefinition extends AICTreeNodeActionDefinition {
  public native let nodeReference: LibTreeDefNodeRef;
  public native let controllersSetupName: LibTreeDefCName;
  public native let useStart: LibTreeDefBool;
  public native let useStop: LibTreeDefBool;
  public native let blendTime: LibTreeDefFloat;
  public native let globalInBlendTime: LibTreeDefFloat;
  public native let globalOutBlendTime: LibTreeDefFloat;
  public native let turnCharacterToMatchVelocity: LibTreeDefBool;
  public native let customStartAnimationName: LibTreeDefCName;
  public native let customMainAnimationName: LibTreeDefCName;
  public native let customStopAnimationName: LibTreeDefCName;
  public native let startSnapToTerrain: LibTreeDefBool;
  public native let mainSnapToTerrain: LibTreeDefBool;
  public native let stopSnapToTerrain: LibTreeDefBool;
  public native let startSnapToTerrainBlendTime: LibTreeDefFloat;
  public native let stopSnapToTerrainBlendTime: LibTreeDefFloat;
}
