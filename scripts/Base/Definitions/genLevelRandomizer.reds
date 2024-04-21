public native class genLevelRandomizer extends GameObject {
  native let entries: array<genLevelRandomizerEntry>;
  native let seed: Uint32;
  native let dataSource: genLevelRandomizerDataSource;
  native let supervisorType: CName;
  native let debugSpawnAll: Bool;
}
