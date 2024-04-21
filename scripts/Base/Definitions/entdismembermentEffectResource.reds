public native class entdismembermentEffectResource extends ISerializable {
  native let Name: CName;
  native let AppearanceNames: array<CName>;
  native let Offset: Transform;
  native let Effect: ResourceAsyncRef; // raRef<worldEffect>
  native let MatchToWoundByName: Bool;
}
