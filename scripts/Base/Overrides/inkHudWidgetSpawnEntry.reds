public native struct inkHudWidgetSpawnEntry {
  public native let hudEntryName: CName;
  public native let enabled: Bool;
  public native let spawnMode: inkSpawnMode;
  public native let widgetResource: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let anchorPlace: inkEAnchor;
  public native let anchorPoint: Vector2;
  public native let margins: inkMargin;
  public native let attachToSlot: Bool;
  public native let slotParams: inkWidgetSlotAttachmentParams;
  public native let useSeparateWindow: Bool;
  public native let ignoreHudSafezones: Bool;
  public native let affectedByGlitchEffect: Bool;
  public native let affectedByBlackwallEffect: Bool;
  public native let spawnBeforeSlots: Bool;
  public native let ignoreHudScaleOverride: Bool;
  public native let hudScalingInterpolationValue: Float;
  public native let hudScalingMarginCorrection: inkMargin;
  // public native let contextVisibility: worlduiContextVisibility;
  // public native let gameContextVisibility: gameuiContext;
  // public native let slotTexture: ref<DynamicTexture>;
  // public native let window: ref<inkVirtualWindow>;
  // public native let slotWidget: ref<inkImage>;
  // public native let rootWidget: ref<inkWidget>;
  // public native let gameController: ref<inkIGameController>;
}
