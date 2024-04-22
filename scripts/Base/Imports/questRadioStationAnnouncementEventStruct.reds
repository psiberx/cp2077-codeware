public native struct questRadioStationAnnouncementEventStruct {
  native let announcementScene: ResourceAsyncRef; // raRef<scnSceneResource>
  native let sceneInput: CName;
  native let queueAnnouncement: Bool;
  native let radioStationName: CName;
  native let blockSignal: Bool;
  native let speaker: audioRadioSpeakerType;
}
