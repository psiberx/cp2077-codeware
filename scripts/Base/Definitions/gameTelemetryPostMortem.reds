public native struct gameTelemetryPostMortem {
  native let crashVisitId: String;
  native let playthroughId: String;
  native let crashVersion: String;
  native let crashPatch: String;
  native let timeCrash: String;
  native let district: String;
  native let zoneType: String;
  native let trackedQuest: gameTelemetryTrackedQuest;
  native let location: Vector3;
  native let sessionLength: Float;
  native let isOom: Bool;
}
