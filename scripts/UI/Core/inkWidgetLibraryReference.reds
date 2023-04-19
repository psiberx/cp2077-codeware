@addMethod(inkWidgetLibraryReference)
public static func Create(path: ResRef, item: CName) -> inkWidgetLibraryReference {
    return new inkWidgetLibraryReference(inkWidgetLibraryResource.Create(path), item);
}
