public native class entEntityTemplate extends resStreamedResource {
  public native let includes: array<entTemplateInclude>;
  public native let appearances: array<entTemplateAppearance>;
  public native let defaultAppearance: CName;
  public native let visualTagsSchema: ref<entVisualTagsSchema>;
  public native let componentResolveSettings: array<entTemplateComponentResolveSettings>;
  public native let bindingOverrides: array<entTemplateBindingOverride>;
  public native let backendDataOverrides: array<entTemplateComponentBackendDataOverrideInfo>;
  public native let resolvedDependencies: array<ResourceAsyncRef>;
  public native let inplaceResources: array<ResourceRef>;
  public native let compiledEntityLODFlags: Uint16;
}
