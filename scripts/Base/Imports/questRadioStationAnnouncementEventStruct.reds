public native struct questRadioStationAnnouncementEventStruct {
  public native let announcementScene: ResourceAsyncRef; // raRef<scnSceneResource>
  public native let sceneInput: CName;
  public native let queueAnnouncement: Bool;
  public native let radioStationName: CName;
  public native let blockSignal: Bool;
  public native let speaker: audioRadioSpeakerType;
}
