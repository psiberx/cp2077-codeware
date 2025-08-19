public native class gameDamageSystemSharedState extends gameIGameSystemReplicatedState {
  public native let hitHistory: array<ref<ServerHitData>>;
  public native let killHistory: array<ref<ServerKillData>>;
}
