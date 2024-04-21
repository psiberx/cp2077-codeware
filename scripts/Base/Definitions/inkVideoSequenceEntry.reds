public native struct inkVideoSequenceEntry {
  native let videoResource: ResourceAsyncRef; // raRef<Bink>
  native let audioEvent: CName;
  native let syncToAudio: Bool;
  native let retriggerAudioOnLoop: Bool;
  native let loop: Bool;
}
