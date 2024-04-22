public native struct grsDeathmatchPlayerGameInfo {
  native let peerID: netPeerID;
  native let isInGame: Bool;
  native let isDead: Bool;
  native let spawnTime: netTime;
  native let killCount: Uint32;
  native let deathCount: Uint32;
  native let lastShooter: netPeerID;
}
