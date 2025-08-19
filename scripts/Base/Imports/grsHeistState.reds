public native struct grsHeistState {
  public native let time: netTime;
  public native let status: grsHeistStatus;
  public native let playersInfo: [grsHeistPlayerGameInfo; 7];
}
