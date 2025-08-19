@neverRef()
public native class gameAppearanceNameVisualTagsPreset_Entity extends ISerializable {
  public native let entityPathHash: Uint64;
  public native let debugEntityPath: CName;
  public native let entityRigPathHash: Uint64;
  public native let debugEntityRigPath: CName;
  public native let commonVisualTags: redTagList;
  public native let appearancesToTags: array<gameAppearanceNameVisualTagsPreset_AppearanceTags>;
}
