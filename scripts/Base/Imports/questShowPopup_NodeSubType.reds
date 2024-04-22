public native class questShowPopup_NodeSubType extends questITutorial_NodeSubType {
  native let path: ref<gameJournalPath>;
  native let open: Bool;
  native let closeAtInput: Bool;
  native let pauseGame: Bool;
  native let hideInMenu: Bool;
  native let margin: inkMargin;
  native let screenMode: questTutorialScreenMode;
  native let position: PopupPosition;
  native let lockPlayerMovement: Bool;
  native let closeCurrentPopup: Bool;
  native let videoType: VideoType;
  native let video: ResourceAsyncRef; // raRef<Bink>
  native let ignoreDisabledTutorials: Bool;
}
