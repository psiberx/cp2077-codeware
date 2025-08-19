public importonly class BakedDestructionComponent extends PhysicalMeshComponent {
  public native let meshFractured: ResourceAsyncRef; // raRef<CMesh>
  public native let meshFracturedAppearance: CName;
  public native let numFrames: Float;
  public native let frameRate: Float;
  public native let playOnlyOnce: Bool;
  public native let restartOnTrigger: Bool;
  public native let disableCollidersOnTrigger: Bool;
  public native let damageThreshold: Float;
  public native let damageEndurance: Float;
  public native let impulseToDamage: Float;
  public native let contactToDamage: Float;
  public native let accumulateDamage: Bool;
  public native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>
  public native let audioMetadata: CName;
}
