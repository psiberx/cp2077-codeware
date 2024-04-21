@addMethod(inkImage)
public func UsesNineSliceScale() -> Bool {
    return this.useNineSliceScale;
}

@addMethod(inkImage)
public func SetNineSliceScale(enable: Bool) {
    this.useNineSliceScale = enable;
}

@addMethod(inkImage)
public func GetNineSliceGrid() -> inkMargin {
    return this.nineSliceScale;
}

@addMethod(inkImage)
public func SetNineSliceGrid(grid: inkMargin) {
    this.nineSliceScale = grid;
}

@addMethod(inkImage)
public func GetTileHAlign() -> inkEHorizontalAlign {
    return this.tileHAlign;
}

@addMethod(inkImage)
public func SetTileHAlign(tileHAlign: inkEHorizontalAlign) {
    this.tileHAlign = tileHAlign;
}

@addMethod(inkImage)
public func GetTileVAlign() -> inkEVerticalAlign {
    return this.tileVAlign;
}

@addMethod(inkImage)
public func SetTileVAlign(tileVAlign: inkEVerticalAlign) {
    this.tileVAlign = tileVAlign;
}
