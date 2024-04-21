public native class animFacialCustomizationSet extends CResource {
  native let baseSetup: ResourceRef; // rRef<animFacialSetup>
  native let targetSetups: array<ResourceAsyncRef>;
  native let targetSetupsTemp: array<animFacialCustomizationTargetEntryTemp>;
  native let numTargets: Uint32;
  native let posesInfo: animFacialSetup_PosesBufferInfo;
  native let jointRegions: array<Uint8>;
  native let usedTransformIndices: array<Uint16>;
  native let numJoints: Uint32;
  native let isCooked: Bool;
}
