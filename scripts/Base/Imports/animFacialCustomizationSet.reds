public native class animFacialCustomizationSet extends CResource {
  public native let baseSetup: ResourceRef; // rRef<animFacialSetup>
  public native let targetSetups: array<ResourceAsyncRef>;
  public native let targetSetupsTemp: array<animFacialCustomizationTargetEntryTemp>;
  public native let numTargets: Uint32;
  public native let posesInfo: animFacialSetup_PosesBufferInfo;
  public native let jointRegions: array<Uint8>;
  public native let usedTransformIndices: array<Uint16>;
  public native let numJoints: Uint32;
  public native let isCooked: Bool;
}
