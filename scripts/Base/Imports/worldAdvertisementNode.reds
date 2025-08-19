public native class worldAdvertisementNode extends worldStaticMeshNode {
  public native let meshInitialScale: Vector3;
  public native let format: AdvertisementFormat;
  public native let adGroupTDBID: TweakDBID;
  public native let enableOverride: Bool;
  public native let adOverrideTDBID: TweakDBID;
  public native let adVersion: Uint32;
  public native let glitchValue: Float;
  public native let lightsData: array<worldAdvertisementLightData>;
}
