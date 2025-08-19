@mixedRef()
public native class audioElevatorSettings extends audioEntitySettings {
  public native let musicEvents: audioMusicController;
  public native let movementEvents: audioLoopingSoundController;
  public native let callingEvent: CName;
  public native let destinationReachedEvent: CName;
  public native let panelSelectionEvent: CName;
}
