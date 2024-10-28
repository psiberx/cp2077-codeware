@addField(inkImage)
native let useExternalDynamicTexture: Bool;

@addField(inkImage)
native let externalDynamicTexture: CName;

@addField(inkImage)
native let useNineSliceScale: Bool;

@addField(inkImage)
native let nineSliceScale: inkMargin;

@addField(inkImage)
native let mirrorType: inkBrushMirrorType;

@addField(inkImage)
native let tileType: inkBrushTileType;

@addField(inkImage)
native let horizontalTileCrop: Float;

@addField(inkImage)
native let verticalTileCrop: Float;

@addField(inkImage)
native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>

@addField(inkImage)
native let texturePart: CName;

@addField(inkImage)
native let contentHAlign: inkEHorizontalAlign;

@addField(inkImage)
native let contentVAlign: inkEVerticalAlign;

@addField(inkImage)
native let tileHAlign: inkEHorizontalAlign;

@addField(inkImage)
native let tileVAlign: inkEVerticalAlign;
