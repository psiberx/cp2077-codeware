public native class vehicleDriveFollowEvent extends Event {
  public native let targetObjToFollow: wref<GameObject>;
  public native let distanceMin: Float;
  public native let distanceMax: Float;
  public native let stopWhenTargetReached: Bool;
  public native let useTraffic: Bool;
}
