@addField(WorldMapMenuGameController)
native let settingsRecordID: TweakDBID;

@addField(WorldMapMenuGameController)
native let playerOnTop: Bool;

@addField(WorldMapMenuGameController)
native let entityPreviewLibraryID: CName;

@addField(WorldMapMenuGameController)
native let floorPlanSpawnContainer: inkCompoundRef;

@addField(WorldMapMenuGameController)
native let compassWidget: inkWidgetRef;

@addField(WorldMapMenuGameController)
native let mappinOutlinesContainer: inkCompoundRef;

@addField(WorldMapMenuGameController)
native let groupOutlinesContainer: inkCompoundRef;

@addField(WorldMapMenuGameController)
native let tooltipDistrictOffset: inkMargin;

@addField(WorldMapMenuGameController)
native let hoveredDistrict: gamedataDistrict;

@addField(WorldMapMenuGameController)
native let hoveredSubDistrict: gamedataDistrict;
