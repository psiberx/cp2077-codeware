public native class vehicleDriveFollowEvent extends Event {
  native let targetObjToFollow: wref<GameObject>;
  native let distanceMin: Float;
  native let distanceMax: Float;
  native let stopWhenTargetReached: Bool;
  native let useTraffic: Bool;
}
