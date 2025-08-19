@neverRef()
public native class gameEntityToAppearancesAndColorVariantsMapEntry extends ISerializable {
  public native let entityPathHash: Uint64;
  public native let debugEntityPath: String;
  public native let appearancesAndTheirColorVariants: array<gameEntityAppearanceColorVariantsArray>;
}
