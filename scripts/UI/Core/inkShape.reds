@addMethod(inkShape)
public func GetResource() -> ResRef {
    return ResourceRef.GetPath(this.shapeResource);
}

@addMethod(inkShape)
public func SetResource(path: ResRef) {
    ResourceRef.LoadPath(this.shapeResource, path);
}

@addMethod(inkShape)
public func GetShape() -> CName {
    return this.shapeName;
}

@addMethod(inkShape)
public func SetShape(shape: CName) {
    this.ChangeShape(shape);
}

@addMethod(inkShape)
public func GetVariant() -> inkEShapeVariant {
    return this.shapeVariant;
}

@addMethod(inkShape)
public func SetVariant(variant: inkEShapeVariant) {
    this.shapeVariant = variant;
}

@addMethod(inkShape)
public func UsesNineSliceScale() -> Bool {
    return this.useNineSlice;
}

@addMethod(inkShape)
public func SetNineSliceScale(enable: Bool) {
    this.useNineSlice = enable;
}

@addMethod(inkShape)
public func GetNineSliceGrid() -> inkMargin {
    return this.nineSliceScale;
}

@addMethod(inkShape)
public func SetNineSliceGrid(grid: inkMargin) {
    this.nineSliceScale = grid;
}


@addMethod(inkShape)
public func GetKeepInBounds() -> Bool {
    return this.keepInBounds;
}

@addMethod(inkShape)
public func GetContentHAlign() -> inkEHorizontalAlign {
    return this.contentHAlign;
}

@addMethod(inkShape)
public func GetContentVAlign() -> inkEVerticalAlign {
    return this.contentVAlign;
}

@addMethod(inkShape)
public func GetBorderColor() -> HDRColor {
    return this.borderColor;
}

@addMethod(inkShape)
public func GetBorderOpacity() -> Float {
    return this.borderOpacity;
}

@addMethod(inkShape)
public func GetFillOpacity() -> Float {
    return this.fillOpacity;
}

@addMethod(inkShape)
public func GetLineThickness() -> Float {
    return this.lineThickness;
}

@addMethod(inkShape)
public func GetEndCapStyle() -> inkEEndCapStyle {
    return this.endCapStyle;
}

@addMethod(inkShape)
public func GetJointStyle() -> inkEJointStyle {
    return this.jointStyle;
}

@addMethod(inkShape)
public func GetVertexList() -> array<Vector2> {
    return this.vertexList;
}

@addMethod(inkShape)
public func SetKeepInBounds(keepInBounds: Bool) {
    this.keepInBounds = keepInBounds;
}

@addMethod(inkShape)
public func SetContentHAlign(contentHAlign: inkEHorizontalAlign) {
    this.contentHAlign = contentHAlign;
}

@addMethod(inkShape)
public func SetContentVAlign(contentVAlign: inkEVerticalAlign) {
    this.contentVAlign = contentVAlign;
}

@addMethod(inkShape)
public func SetBorderColor(borderColor: HDRColor) {
    this.borderColor = borderColor;
}

@addMethod(inkShape)
public func SetBorderOpacity(borderOpacity: Float) {
    this.borderOpacity = borderOpacity;
}

@addMethod(inkShape)
public func SetFillOpacity(fillOpacity: Float) {
    this.fillOpacity = fillOpacity;
}

@addMethod(inkShape)
public func SetLineThickness(lineThickness: Float) {
    this.lineThickness = lineThickness;
}

@addMethod(inkShape)
public func SetEndCapStyle(endCapStyle: inkEEndCapStyle) {
    this.endCapStyle = endCapStyle;
}

@addMethod(inkShape)
public func SetJointStyle(jointStyle: inkEJointStyle) {
    this.jointStyle = jointStyle;
}

@addMethod(inkShape)
public func SetVertexList(vertexList: array<Vector2>) {
    this.vertexList = vertexList;
}
