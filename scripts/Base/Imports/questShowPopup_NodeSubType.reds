public native class questShowPopup_NodeSubType extends questITutorial_NodeSubType {
  public native let path: ref<gameJournalPath>;
  public native let open: Bool;
  public native let closeAtInput: Bool;
  public native let pauseGame: Bool;
  public native let hideInMenu: Bool;
  public native let margin: inkMargin;
  public native let screenMode: questTutorialScreenMode;
  public native let position: PopupPosition;
  public native let lockPlayerMovement: Bool;
  public native let closeCurrentPopup: Bool;
  public native let videoType: VideoType;
  public native let video: ResourceAsyncRef; // raRef<Bink>
  public native let ignoreDisabledTutorials: Bool;
}
