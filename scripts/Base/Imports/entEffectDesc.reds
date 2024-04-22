public native class entEffectDesc extends ISerializable {
  native let id: CRUID;
  native let effectName: CName;
  native let effect: ResourceAsyncRef; // raRef<worldEffect>
  native let compiledEffectInfo: worldCompiledEffectInfo;
  native let autoSpawnTag: CName;
  native let isAutoSpawn: Bool;
  native let randomWeight: Uint8;
}
