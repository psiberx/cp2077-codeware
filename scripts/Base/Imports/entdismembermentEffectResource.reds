public native class entdismembermentEffectResource extends ISerializable {
  public native let Name: CName;
  public native let AppearanceNames: array<CName>;
  public native let Offset: Transform;
  public native let Effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let MatchToWoundByName: Bool;
}
