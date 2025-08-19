@addField(MeshComponent)
public native let mesh: ResourceAsyncRef; // raRef<CMesh>

@addField(MeshComponent)
public native let meshAppearance: CName;

@addField(MeshComponent)
public native let castShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
public native let castLocalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
public native let castRayTracedGlobalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
public native let castRayTracedLocalShadows: shadowsShadowCastingMode;

@addField(MeshComponent)
public native let motionBlurScale: Float;

@addField(MeshComponent)
public native let visualScale: Vector3;

@addField(MeshComponent)
public native let renderingPlane: ERenderingPlane;

@addField(MeshComponent)
public native let objectTypeID: ERenderObjectType;

@addField(MeshComponent)
public native let numInstances: Uint32;

@addField(MeshComponent)
public native let chunkMask: Uint64;

@addField(MeshComponent)
public native let order: Uint8;

@addField(MeshComponent)
public native let isEnabled: Bool;

@addField(MeshComponent)
public native let LODMode: entMeshComponentLODMode;

@addField(MeshComponent)
public native let forcedLodDistance: entForcedLodDistance;

@addField(MeshComponent)
public native let overrideMeshNavigationImpact: Bool;

@addField(MeshComponent)
public native let navigationImpact: NavGenNavigationSetting;

@addField(MeshComponent)
public native let version: Uint8;
