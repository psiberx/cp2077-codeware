@addField(inkShape)
public native let shapeResource: ResourceRef; // rRef<inkShapeCollectionResource>

@addField(inkShape)
public native let shapeName: CName;

@addField(inkShape)
public native let shapeVariant: inkEShapeVariant;

@addField(inkShape)
public native let keepInBounds: Bool;

@addField(inkShape)
public native let nineSliceScale: inkMargin;

@addField(inkShape)
public native let useNineSlice: Bool;

@addField(inkShape)
public native let contentHAlign: inkEHorizontalAlign;

@addField(inkShape)
public native let contentVAlign: inkEVerticalAlign;

@addField(inkShape)
public native let borderColor: HDRColor;

@addField(inkShape)
public native let borderOpacity: Float;

@addField(inkShape)
public native let fillOpacity: Float;

@addField(inkShape)
public native let lineThickness: Float;

@addField(inkShape)
public native let endCapStyle: inkEEndCapStyle;

@addField(inkShape)
public native let jointStyle: inkEJointStyle;

@addField(inkShape)
public native let vertexList: array<Vector2>;
