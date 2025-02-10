@neverRef() public native class animFacialSetup extends CResource {
  native let rig: ResourceRef; // rRef<animRig>
  native let inputRig: ResourceRef; // rRef<animRig>
  native let info: animFacialSetup_BufferInfo;
  native let posesInfo: animFacialSetup_PosesBufferInfo;
  native let usedTransformIndices: array<Uint16>;
  native let useFemaleAnimSet: Bool;
  native let version: Uint32;
}

