public importonly class BakedDestructionComponent extends PhysicalMeshComponent {
  native let meshFractured: ResourceAsyncRef; // raRef<CMesh>
  native let meshFracturedAppearance: CName;
  native let numFrames: Float;
  native let frameRate: Float;
  native let playOnlyOnce: Bool;
  native let restartOnTrigger: Bool;
  native let disableCollidersOnTrigger: Bool;
  native let damageThreshold: Float;
  native let damageEndurance: Float;
  native let impulseToDamage: Float;
  native let contactToDamage: Float;
  native let accumulateDamage: Bool;
  native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>
  native let audioMetadata: CName;
}
