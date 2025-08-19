public native struct inkVideoSequenceEntry {
  public native let videoResource: ResourceAsyncRef; // raRef<Bink>
  public native let audioEvent: CName;
  public native let syncToAudio: Bool;
  public native let retriggerAudioOnLoop: Bool;
  public native let loop: Bool;
}
