public native struct inkLanguageFontMapping {
  native let languageCode: CName;
  native let font: ResourceAsyncRef; // raRef<inkFontFamilyResource>
  native let fontSizeModifier: Int16;
  native let trackingModifier: Uint32;
  native let lineHeightModifier: Float;
  native let fontSizeModifierFloat: Float;
  native let styleModifer: CName;
}
