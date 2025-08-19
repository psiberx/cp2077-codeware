@mixedRef()
public native class audioDoorsSettings extends audioDeviceSettings {
  public native let openEvent: CName;
  public native let openFailedEvent: CName;
  public native let closeEvent: CName;
  public native let lockEvent: CName;
  public native let unlockEvent: CName;
  public native let sealEvent: CName;
  public native let soundBank: CName;
}
