@addField(MeshComponent)
native let mesh: ResourceAsyncRef; // raRef<CMesh>

@addField(MeshComponent)
native let meshAppearance: CName;

@addField(MeshComponent)
native let castShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
native let castLocalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
native let castRayTracedGlobalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
native let castRayTracedLocalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
native let motionBlurScale: Float;

@addField(MeshComponent)
native let visualScale: Vector3;

@addField(MeshComponent)
native let renderingPlane: ERenderingPlane;

@addField(MeshComponent)
native let objectTypeID: ERenderObjectType;

@addField(MeshComponent)
native let numInstances: Uint32;

@addField(MeshComponent)
native let chunkMask: Uint64;

@addField(MeshComponent)
native let order: Uint8;

@addField(MeshComponent)
native let isEnabled: Bool;

@addField(MeshComponent)
native let LODMode: entMeshComponentLODMode;

@addField(MeshComponent)
native let forcedLodDistance: entForcedLodDistance;

@addField(MeshComponent)
native let overrideMeshNavigationImpact: Bool;

@addField(MeshComponent)
native let navigationImpact: NavGenNavigationSetting;

@addField(MeshComponent)
native let version: Uint8;
