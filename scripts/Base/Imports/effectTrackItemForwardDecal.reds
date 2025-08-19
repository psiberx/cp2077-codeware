public native class effectTrackItemForwardDecal extends effectTrackItem {
  public native let mesh: ResourceRef; // rRef<CMesh>
  public native let appearance: CName;
  public native let scale: ref<IEvaluatorVector>;
  public native let additionalRotation: Float;
  public native let sizeThreshold: Float;
  public native let randomRotation: Bool;
  public native let randomAppearance: Bool;
  public native let isAttached: Bool;
  public native let subUVx: Uint32;
  public native let subUVy: Uint32;
  public native let frame: Uint32;
  public native let fadeOutTime: Float;
  public native let fadeInTime: Float;
}
