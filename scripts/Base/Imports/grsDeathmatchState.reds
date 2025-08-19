public native struct grsDeathmatchState {
  public native let time: netTime;
  public native let status: grsDeathmatchStatus;
  public native let sessionLength: netTime;
  public native let playersInfo: [grsDeathmatchPlayerGameInfo; 7];
}
