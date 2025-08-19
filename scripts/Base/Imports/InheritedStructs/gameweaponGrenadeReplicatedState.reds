public native struct gameweaponGrenadeReplicatedState {
  public native let recordID: TweakDBID;
  public native let persistentID: Uint64;
  public native let instigator: wref<GameObject>;
  public native let itemID: ItemID;
  public native let currentTransform: WorldTransform;
  public native let exploded: Bool;
  public native let launched: Bool;
}
