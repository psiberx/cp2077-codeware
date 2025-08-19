public native class gameuiarcadeShooterSpawnController extends inkLogicController {
  public native let enemyType: gameuiarcadeShooterAIType;
  public native let spawnCondition: gameuiarcadeShooterSpawnerCondition;
  public native let spawnDelay: Float;
  public native let spawnCount: Uint32;
  public native let offScreenSpawnExpiryTime: Float;
  public native let skippable: Bool;
  public native let skipOffset: Float;
  public native let awaitPreviousUnitDead: Bool;
  public native let enemyParameter: String;
}
