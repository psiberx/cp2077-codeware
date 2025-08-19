public native class SensorObject extends ISerializable {
  public native let presetID: TweakDBID;
  public native let detectionFactor: Float;
  public native let detectionDropFactor: Float;
  public native let detectionCoolDownTime: Float;
  public native let detectionPartCoolDownTime: Float;
  public native let hearingEnabled: Bool;
  public native let sensorObjectType: gamedataSenseObjectType;
}
