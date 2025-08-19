public native class appearanceAppearanceResource extends resStreamedResource {
  public native let alternateAppearanceSettingName: CName;
  public native let alternateAppearanceSuffixes: array<CName>;
  public native let alternateAppearanceMapping: array<appearanceAlternateAppearanceEntry>;
  public native let censorshipMapping: array<appearanceCensorshipEntry>;
  public native let Wounds: array<ref<entdismembermentWoundResource>>;
  public native let DismEffects: array<ref<entdismembermentEffectResource>>;
  public native let DismWoundConfig: entdismembermentWoundsConfigSet;
  public native let baseType: CName;
  public native let baseEntityType: CName;
  public native let baseEntity: ResourceAsyncRef; // raRef<entEntityTemplate>
  public native let partType: CName;
  public native let preset: CName;
  public native let appearances: array<ref<appearanceAppearanceDefinition>>;
  public native let commonCookData: ResourceAsyncRef; // raRef<appearanceCookedAppearanceData>
  public native let proxyPolyCount: Int32;
  public native let forceCompileProxy: Bool;
  public native let generatePlayerBlockingCollisionForProxy: Bool;
}
