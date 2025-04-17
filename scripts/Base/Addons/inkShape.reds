@addField(inkShape)
native let shapeResource: ResourceRef; // rRef<inkShapeCollectionResource>

@addField(inkShape)
native let shapeName: CName;

@addField(inkShape)
native let shapeVariant: inkEShapeVariant;

@addField(inkShape)
native let keepInBounds: Bool;

@addField(inkShape)
native let nineSliceScale: inkMargin;

@addField(inkShape)
native let useNineSlice: Bool;

@addField(inkShape)
native let contentHAlign: inkEHorizontalAlign;

@addField(inkShape)
native let contentVAlign: inkEVerticalAlign;

@addField(inkShape)
native let borderColor: HDRColor;

@addField(inkShape)
native let borderOpacity: Float;

@addField(inkShape)
native let fillOpacity: Float;

@addField(inkShape)
native let lineThickness: Float;

@addField(inkShape)
native let endCapStyle: inkEEndCapStyle;

@addField(inkShape)
native let jointStyle: inkEJointStyle;

@addField(inkShape)
native let vertexList: array<Vector2>;
