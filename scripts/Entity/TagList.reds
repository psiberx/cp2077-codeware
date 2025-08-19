public native struct TagList {
    public native let tags: array<CName>;

    public static native func IsEmpty(self: script_ref<TagList>) -> Bool
    public static native func Clear(self: script_ref<TagList>)

    public static native func HasTag(self: script_ref<TagList>, tag: CName) -> Bool
    public static native func AddTag(self: script_ref<TagList>, tag: CName)
    public static native func RemoveTag(self: script_ref<TagList>, tag: CName)

    public static native func HasTags(self: script_ref<TagList>, tags: array<CName>) -> Bool
    public static native func AddTags(self: script_ref<TagList>, tags: array<CName>)
    public static native func RemoveTags(self: script_ref<TagList>, tags: array<CName>)
}
