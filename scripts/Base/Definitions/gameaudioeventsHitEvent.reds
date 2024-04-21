public native class gameaudioeventsHitEvent extends Event {
  native let attackType: gamedataAttackType;
  native let hitPosition: Vector4;
  native let physicsMaterial: CName;
  native let damage: Float;
  native let isTargetPuppet: Bool;
  native let targetPuppetMeleeMaterial: CName;
  native let isTargetPuppetHead: Bool;
}
