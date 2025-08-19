@addField(worlduiWidgetComponent)
public native let cursorResource: ResourceRef; // rRef<inkWidgetLibraryResource>

@addField(worlduiWidgetComponent)
public native let widgetResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>

@addField(worlduiWidgetComponent)
public native let itemNameToSpawn: CName;

@addField(worlduiWidgetComponent)
public native let staticTextureResource: ResourceAsyncRef; // raRef<CBitmapTexture>

@addField(worlduiWidgetComponent)
public native let sceneWidgetProperties: worlduiSceneWidgetProperties;

@addField(worlduiWidgetComponent)
public native let spawnDistanceOverride: Float;

@addField(worlduiWidgetComponent)
public native let limitedSpawnDistanceFromVehicle: Bool;
