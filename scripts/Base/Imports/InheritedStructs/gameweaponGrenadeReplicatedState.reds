public native struct gameweaponGrenadeReplicatedState {
  native let recordID: TweakDBID;
  native let persistentID: Uint64;
  native let instigator: wref<GameObject>;
  native let itemID: ItemID;
  native let currentTransform: WorldTransform;
  native let exploded: Bool;
  native let launched: Bool;
}
