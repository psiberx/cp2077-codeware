public native struct gameTelemetryPostMortem {
  public native let crashVisitId: String;
  public native let playthroughId: String;
  public native let crashVersion: String;
  public native let crashPatch: String;
  public native let timeCrash: String;
  public native let district: String;
  public native let zoneType: String;
  public native let trackedQuest: gameTelemetryTrackedQuest;
  public native let location: Vector3;
  public native let sessionLength: Float;
  public native let isOom: Bool;
}
