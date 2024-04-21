public native class AICTreeNodeActionAnimationCurvePathDefinition extends AICTreeNodeActionDefinition {
  native let nodeReference: LibTreeDefNodeRef;
  native let controllersSetupName: LibTreeDefCName;
  native let useStart: LibTreeDefBool;
  native let useStop: LibTreeDefBool;
  native let blendTime: LibTreeDefFloat;
  native let globalInBlendTime: LibTreeDefFloat;
  native let globalOutBlendTime: LibTreeDefFloat;
  native let turnCharacterToMatchVelocity: LibTreeDefBool;
  native let customStartAnimationName: LibTreeDefCName;
  native let customMainAnimationName: LibTreeDefCName;
  native let customStopAnimationName: LibTreeDefCName;
  native let startSnapToTerrain: LibTreeDefBool;
  native let mainSnapToTerrain: LibTreeDefBool;
  native let stopSnapToTerrain: LibTreeDefBool;
  native let startSnapToTerrainBlendTime: LibTreeDefFloat;
  native let stopSnapToTerrainBlendTime: LibTreeDefFloat;
}
