public native class entEffectDesc extends ISerializable {
  public native let id: CRUID;
  public native let effectName: CName;
  public native let effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let compiledEffectInfo: worldCompiledEffectInfo;
  public native let autoSpawnTag: CName;
  public native let isAutoSpawn: Bool;
  public native let randomWeight: Uint8;
}
