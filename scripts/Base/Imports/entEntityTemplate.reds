public native class entEntityTemplate extends resStreamedResource {
  native let includes: array<entTemplateInclude>;
  native let appearances: array<entTemplateAppearance>;
  native let defaultAppearance: CName;
  native let visualTagsSchema: ref<entVisualTagsSchema>;
  native let componentResolveSettings: array<entTemplateComponentResolveSettings>;
  native let bindingOverrides: array<entTemplateBindingOverride>;
  native let backendDataOverrides: array<entTemplateComponentBackendDataOverrideInfo>;
  native let resolvedDependencies: array<ResourceAsyncRef>;
  native let inplaceResources: array<ResourceRef>;
  native let compiledEntityLODFlags: Uint16;
}
