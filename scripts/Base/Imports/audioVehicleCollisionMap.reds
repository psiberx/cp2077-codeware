public native class audioVehicleCollisionMap extends audioAudioMetadata {
  native let minImpactVelocityThreshold: Float;
  native let minRumbleVelocityThreshold: Float;
  native let rumbleCooldown: Float;
  native let scrapingMinTangentialVelocityThreshold: Float;
  native let scrapingMaxCollisionCooldown: Float;
  native let scrapingMinVehicleUpCollisionContactAngle: Float;
  native let useScrapingMinVehicleUpCollisionContactAngle: Bool;
  native let explosionEvent: CName;
  native let bigFireEvent: CName;
  native let engineFireEvent: CName;
  native let coolerDamageEvent: CName;
  native let interiorCollisionEvent: CName;
  native let collisionSettings: array<audioVehicleCollisionMapItem>;
}
