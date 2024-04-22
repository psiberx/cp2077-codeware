public native class worldAdvertisementNode extends worldStaticMeshNode {
  native let meshInitialScale: Vector3;
  native let format: AdvertisementFormat;
  native let adGroupTDBID: TweakDBID;
  native let enableOverride: Bool;
  native let adOverrideTDBID: TweakDBID;
  native let adVersion: Uint32;
  native let glitchValue: Float;
  native let lightsData: array<worldAdvertisementLightData>;
}
