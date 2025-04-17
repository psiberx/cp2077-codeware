@addField(MinimapContainerController)
native let settings: ref<MinimapSettings>;

@addField(MinimapContainerController)
native let clampedMappinContainer: inkCompoundRef;

@addField(MinimapContainerController)
native let unclampedMappinContainer: inkCompoundRef;

@addField(MinimapContainerController)
native let maskWidget: inkMaskRef;

@addField(MinimapContainerController)
native let playerIconWidget: inkWidgetRef;

@addField(MinimapContainerController)
native let compassWidget: inkWidgetRef;

@addField(MinimapContainerController)
native let worldGeometryContainer: inkCanvasRef;

@addField(MinimapContainerController)
native let worldGeometryCache: inkCacheRef;

@addField(MinimapContainerController)
native let geometryLibraryID: CName;

@addField(MinimapContainerController)
native let timeDisplayWidget: inkCompoundRef;
