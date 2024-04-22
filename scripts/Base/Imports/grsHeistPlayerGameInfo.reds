public native struct grsHeistPlayerGameInfo {
  native let peerID: netPeerID;
  native let isInGame: Bool;
  native let isReady: Bool;
  native let isRespawning: Bool;
  native let isDead: Bool;
  native let spawnTime: netTime;
  native let killCount: Uint32;
  native let deathCount: Uint32;
  native let characterRecord: String;
}
