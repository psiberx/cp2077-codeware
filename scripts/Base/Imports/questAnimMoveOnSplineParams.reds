public native struct questAnimMoveOnSplineParams {
  native let controllersSetupName: CName;
  native let blendTime: Float;
  native let globalInBlendTime: Float;
  native let globalOutBlendTime: Float;
  native let turnCharacterToMatchVelocity: Bool;
  native let customStartAnimationName: CName;
  native let customMainAnimationName: CName;
  native let customStopAnimationName: CName;
  native let startSnapToTerrain: Bool;
  native let mainSnapToTerrain: Bool;
  native let stopSnapToTerrain: Bool;
  native let startSnapToTerrainBlendTime: Float;
  native let stopSnapToTerrainBlendTime: Float;
}
