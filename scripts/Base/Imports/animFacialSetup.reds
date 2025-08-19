public native class animFacialSetup extends CResource {
  public native let rig: ResourceRef; // rRef<animRig>
  public native let inputRig: ResourceRef; // rRef<animRig>
  public native let info: animFacialSetup_BufferInfo;
  public native let posesInfo: animFacialSetup_PosesBufferInfo;
  public native let usedTransformIndices: array<Uint16>;
  public native let useFemaleAnimSet: Bool;
  public native let version: Uint32;
}
