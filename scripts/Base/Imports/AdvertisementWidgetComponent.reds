public native class AdvertisementWidgetComponent extends IWorldWidgetComponent {
  public native let format: AdvertisementFormat;
  public native let adGroupTDBID: TweakDBID;
  public native let enableOverride: Bool;
  public native let adOverrideTDBID: TweakDBID;
  public native let adVersion: Uint32;
  public native let useOnlyAttachedLights: Bool;

  public final native func GetLocalizedDescription()
}
