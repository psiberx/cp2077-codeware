public native class gameuiarcadeShooterSpawnController extends inkLogicController {
  native let enemyType: gameuiarcadeShooterAIType;
  native let spawnCondition: gameuiarcadeShooterSpawnerCondition;
  native let spawnDelay: Float;
  native let spawnCount: Uint32;
  native let offScreenSpawnExpiryTime: Float;
  native let skippable: Bool;
  native let skipOffset: Float;
  native let awaitPreviousUnitDead: Bool;
  native let enemyParameter: String;
}
