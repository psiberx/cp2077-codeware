public native class SensorObject extends ISerializable {
  native let presetID: TweakDBID;
  native let detectionFactor: Float;
  native let detectionDropFactor: Float;
  native let detectionCoolDownTime: Float;
  native let detectionPartCoolDownTime: Float;
  native let hearingEnabled: Bool;
  native let sensorObjectType: gamedataSenseObjectType;
}
