@addMethod(inkWidgetLibraryResource)
public static native func SetPath(self: script_ref<inkWidgetLibraryResource>, path: ResRef);

@addMethod(inkWidgetLibraryResource)
public static func Create(path: ResRef) -> inkWidgetLibraryResource {
    let ref: inkWidgetLibraryResource;
    inkWidgetLibraryResource.SetPath(ref, path);
    return ref;
}
