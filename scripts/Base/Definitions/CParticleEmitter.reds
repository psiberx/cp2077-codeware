public native class CParticleEmitter extends IParticleModule {
  native let positionX: Int32;
  native let positionY: Int32;
  native let material: ResourceRef; // rRef<IMaterial>
  native let maxParticles: Uint16;
  native let diffuseWrapFactor: Float;
  native let backLightingFactor: Float;
  native let lightingMipBias: Uint32;
  native let emitterLoops: Int8;
  native let maskInsideCar: Bool;
  native let maskInsideInterior: Bool;
  native let maskAboveWater: Bool;
  native let maskUnderWater: Bool;
  native let useSubFrameEmission: Bool;
  native let keepSimulationLocal: Bool;
  native let killOnCollision: Bool;
  native let initialParticleCount: Uint8;
  native let envColorGroup: EEnvColorGroup;
  native let emitterGroup: EEmitterGroup;
  native let renderObjectType: ERenderObjectType;
  native let windInfluence: Float;
  native let internalPriority: Uint8;
  native let lods: array<SParticleEmitterLODLevel>;
  native let Enabled: Bool;
  native let Relative: Bool;
  native let UseEnvironmentFogColor: Bool;
  native let Color: HDRColor;
  native let Size: Float;
  native let Density: Float;
  native let Falloff: Float;
  native let NoiseScale: Float;
  native let NoiseThreshold: Float;
  native let NoiseVelocity: Vector3;
}
