public native class effectTrackItemForwardDecal extends effectTrackItem {
  native let mesh: ResourceRef; // rRef<CMesh>
  native let appearance: CName;
  native let additionalRotation: Float;
  native let sizeThreshold: Float;
  native let randomRotation: Bool;
  native let randomAppearance: Bool;
  native let isAttached: Bool;
  native let subUVx: Uint32;
  native let subUVy: Uint32;
  native let frame: Uint32;
  native let fadeOutTime: Float;
  native let fadeInTime: Float;
}
