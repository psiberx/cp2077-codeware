public native class gameDamageSystemSharedState extends gameIGameSystemReplicatedState {
  native let hitHistory: array<ref<ServerHitData>>;
  native let killHistory: array<ref<ServerKillData>>;
}
