public native struct gameuiHudScalingSensitiveWidget {
  native let widget: inkWidgetRef;
  native let adjustScale: Bool;
  native let adjustTranslation: Bool;
  native let adjustMargin: Bool;
  native let targetMarginAtDoubleScale: inkMargin;
  native let marginToScalecorrectOverride: inkMargin;
}
