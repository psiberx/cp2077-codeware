@addMethod(inkWidgetLibraryReference)
public static func Create(path: ResRef, item: CName) -> inkWidgetLibraryReference {
    return inkWidgetLibraryReference(inkWidgetLibraryResource.Create(path), item);
}
