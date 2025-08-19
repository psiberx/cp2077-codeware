public native class gameaudioeventsHitEvent extends Event {
  public native let attackType: gamedataAttackType;
  public native let hitPosition: Vector4;
  public native let physicsMaterial: CName;
  public native let damage: Float;
  public native let isTargetPuppet: Bool;
  public native let targetPuppetMeleeMaterial: CName;
  public native let isTargetPuppetHead: Bool;
}
