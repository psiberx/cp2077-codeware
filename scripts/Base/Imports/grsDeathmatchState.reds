public native struct grsDeathmatchState {
  native let time: netTime;
  native let status: grsDeathmatchStatus;
  native let sessionLength: netTime;
  native let playersInfo: [grsDeathmatchPlayerGameInfo; 7];
}
