public native struct grsHeistPlayerGameInfo {
  public native let peerID: netPeerID;
  public native let isInGame: Bool;
  public native let isReady: Bool;
  public native let isRespawning: Bool;
  public native let isDead: Bool;
  public native let spawnTime: netTime;
  public native let killCount: Uint32;
  public native let deathCount: Uint32;
  public native let characterRecord: String;
}
