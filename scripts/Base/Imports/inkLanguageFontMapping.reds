public native struct inkLanguageFontMapping {
  public native let languageCode: CName;
  public native let font: ResourceAsyncRef; // raRef<inkFontFamilyResource>
  public native let fontSizeModifier: Int16;
  public native let trackingModifier: Uint32;
  public native let lineHeightModifier: Float;
  public native let fontSizeModifierFloat: Float;
  public native let styleModifer: CName;
}
