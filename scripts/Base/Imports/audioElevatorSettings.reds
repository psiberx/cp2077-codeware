public native class audioElevatorSettings extends audioEntitySettings {
  native let musicEvents: audioMusicController;
  native let movementEvents: audioLoopingSoundController;
  native let callingEvent: CName;
  native let destinationReachedEvent: CName;
  native let panelSelectionEvent: CName;
}
