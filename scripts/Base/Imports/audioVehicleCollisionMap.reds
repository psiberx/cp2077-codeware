@mixedRef()
public native class audioVehicleCollisionMap extends audioAudioMetadata {
  public native let minImpactVelocityThreshold: Float;
  public native let minRumbleVelocityThreshold: Float;
  public native let rumbleCooldown: Float;
  public native let scrapingMinTangentialVelocityThreshold: Float;
  public native let scrapingMaxCollisionCooldown: Float;
  public native let scrapingMinVehicleUpCollisionContactAngle: Float;
  public native let useScrapingMinVehicleUpCollisionContactAngle: Bool;
  public native let explosionEvent: CName;
  public native let bigFireEvent: CName;
  public native let engineFireEvent: CName;
  public native let coolerDamageEvent: CName;
  public native let interiorCollisionEvent: CName;
  public native let collisionSettings: array<audioVehicleCollisionMapItem>;
}
