public native class appearanceAppearanceDefinition extends ISerializable {
  public native let name: CName;
  public native let parentAppearance: CName;
  public native let partsMasks: array<array<CName>>;
  public native let partsValues: array<appearanceAppearancePart>;
  public native let partsOverrides: array<appearanceAppearancePartOverrides>;
  public native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let forcedLodDistance: Uint8;
  public native let proxyMeshAppearance: CName;
  public native let cookedDataPathOverride: ResourceAsyncRef; // raRef<CResource>
  public native let parametersBuffer: entEntityParametersBuffer;
  public native let visualTags: redTagList;
  public native let inheritedVisualTags: redTagList;
  public native let hitRepresentationOverrides: array<HitRepresentationOverride>;
  public native let resolvedDependencies: array<ResourceAsyncRef>;
  public native let looseDependencies: array<ResourceAsyncRef>;
  public native let censorFlags: Uint32;
}
