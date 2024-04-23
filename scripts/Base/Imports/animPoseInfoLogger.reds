public native struct animPoseInfoLogger {
  native let enabled: Bool;
  native let showStackTransformsCount: Bool;
  native let showStackTracksCount: Bool;
  native let entries: array<ref<animPoseInfoLoggerEntry>>;
}
