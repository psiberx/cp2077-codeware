public native class appearanceAppearanceDefinition extends ISerializable {
  native let name: CName;
  native let parentAppearance: CName;
  native let partsMasks: array<array<CName>>;
  native let partsValues: array<appearanceAppearancePart>;
  native let partsOverrides: array<appearanceAppearancePartOverrides>;
  native let proxyMesh: ResourceAsyncRef; // raRef<CMesh>
  native let forcedLodDistance: Uint8;
  native let proxyMeshAppearance: CName;
  native let cookedDataPathOverride: ResourceAsyncRef; // raRef<CResource>
  native let parametersBuffer: entEntityParametersBuffer;
  native let visualTags: redTagList;
  native let inheritedVisualTags: redTagList;
  native let hitRepresentationOverrides: array<HitRepresentationOverride>;
  native let resolvedDependencies: array<ResourceAsyncRef>;
  native let looseDependencies: array<ResourceAsyncRef>;
  native let censorFlags: Uint32;
}
