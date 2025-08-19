@mixedRef()
public native class audioNpcWeaponSettings extends audioWeaponSettings {
  public native let gunChoir: CName;
  public native let tails: CName;
  public native let obstructionEnabled: Bool;
  public native let occlusionEnabled: Bool;
  public native let repositionEnabled: Bool;
  public native let obstructionChangeTime: Float;
  public native let disablePathfinding: Bool;
  public native let voiceSwitchCooldown: Float;
  public native let reloadSound: CName;
  public native let quickMeleeAttackSound: CName;
  public native let quickMeleeHitSound: CName;
}
