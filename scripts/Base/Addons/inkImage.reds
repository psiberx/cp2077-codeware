@addField(inkImage)
public native let useExternalDynamicTexture: Bool;

@addField(inkImage)
public native let externalDynamicTexture: CName;

@addField(inkImage)
public native let useNineSliceScale: Bool;

@addField(inkImage)
public native let nineSliceScale: inkMargin;

@addField(inkImage)
public native let mirrorType: inkBrushMirrorType;

@addField(inkImage)
public native let tileType: inkBrushTileType;

@addField(inkImage)
public native let horizontalTileCrop: Float;

@addField(inkImage)
public native let verticalTileCrop: Float;

@addField(inkImage)
public native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>

@addField(inkImage)
public native let texturePart: CName;

@addField(inkImage)
public native let contentHAlign: inkEHorizontalAlign;

@addField(inkImage)
public native let contentVAlign: inkEVerticalAlign;

@addField(inkImage)
public native let tileHAlign: inkEHorizontalAlign;

@addField(inkImage)
public native let tileVAlign: inkEVerticalAlign;
