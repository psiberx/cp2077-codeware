@addMethod(inkMask)
public func GetTextureAtlas() -> ResRef {
    return ResourceAsyncRef.GetPath(this.textureAtlas);
}

@addMethod(inkMask)
public func SetTextureAtlas(path: ResRef) {
    ResourceAsyncRef.SetPath(this.textureAtlas, path);
}

@addMethod(inkMask)
public func GetDynamicTexture() -> CName {
    return this.dynamicTextureMask;
}

@addMethod(inkMask)
public func SetDynamicTexture(value: CName) {
    this.dynamicTextureMask = value;
}

@addMethod(inkMask)
public func GetDataSource() -> inkMaskDataSource {
    return this.dataSource;
}

@addMethod(inkMask)
public func SetDataSource(value: inkMaskDataSource) {
    this.dataSource = value;
}

@addMethod(inkMask)
public func IsInverted() -> Bool {
    return this.invertMask;
}

@addMethod(inkMask)
public func SetInverted(value: Bool) {
    this.invertMask = value;
}

@addMethod(inkMask)
public func GetTransparency() -> Float {
    return this.maskTransparency;
}

@addMethod(inkMask)
public func SetTransparency(value: Float) {
    this.maskTransparency = value;
}
