@addField(worlduiWidgetComponent)
native let cursorResource: ResourceRef; // rRef<inkWidgetLibraryResource>

@addField(worlduiWidgetComponent)
native let widgetResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>

@addField(worlduiWidgetComponent)
native let itemNameToSpawn: CName;

@addField(worlduiWidgetComponent)
native let staticTextureResource: ResourceAsyncRef; // raRef<CBitmapTexture>

@addField(worlduiWidgetComponent)
native let sceneWidgetProperties: worlduiSceneWidgetProperties;

@addField(worlduiWidgetComponent)
native let spawnDistanceOverride: Float;

@addField(worlduiWidgetComponent)
native let limitedSpawnDistanceFromVehicle: Bool;
