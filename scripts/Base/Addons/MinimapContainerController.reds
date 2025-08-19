@addField(MinimapContainerController)
public native let settings: ref<MinimapSettings>;

@addField(MinimapContainerController)
public native let clampedMappinContainer: inkCompoundRef;

@addField(MinimapContainerController)
public native let unclampedMappinContainer: inkCompoundRef;

@addField(MinimapContainerController)
public native let maskWidget: inkMaskRef;

@addField(MinimapContainerController)
public native let playerIconWidget: inkWidgetRef;

@addField(MinimapContainerController)
public native let compassWidget: inkWidgetRef;

@addField(MinimapContainerController)
public native let worldGeometryContainer: inkCanvasRef;

@addField(MinimapContainerController)
public native let worldGeometryCache: inkCacheRef;

@addField(MinimapContainerController)
public native let geometryLibraryID: CName;

@addField(MinimapContainerController)
public native let timeDisplayWidget: inkCompoundRef;
